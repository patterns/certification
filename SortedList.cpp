// SortedList.cpp; Hsin-ih Tu; 2025.10.16;
// Definition of sorted circular double linked list
//

// List constructor
template <typename T>
SortedList<T>::SortedList() : length_(0) {
   SListNode<T> *dummy = new SListNode<T>(HeadNode, true);
   header = dummy;
}

// List deconstructor
template <typename T>
SortedList<T>::~SortedList() {
   clear();
   delete header;
}

// List copy-constructor
// (implement pass and return by value)
template <typename T>
SortedList<T>::SortedList(const SortedList<T> &rhs) {
   // TODO sanity check on rhs param

   header = rhs.header->clone();
   length_ = rhs.length_;
}

// Element identity
template <typename T>
bool SortedList<T>::elementMatch(SListNode<T> *n, T elem) const {
   return n->elementMatch(elem);
}

// node creation
template <typename T>
bool SortedList<T>::insert(T elem) {
   if (empty()) {  // empty list
      SListNode<T> *newNode = new SListNode<T>(elem);
      newNode->initialize(elem, header, header);
      header->next_ = newNode;
      header->prev_ = newNode;
      length_++;
      return true;
   }

   SListNode<T> *n0 = zeroNode();
   SListNode<T> *n1 = n0->child();
   if (n1->isHeadNode()) {           // single node
      if (elementMatch(n0, elem)) {  // node already exists
         n0->counterPlus();          // increment duplicate counter
         length_++;
         return true;
      }

      // create new n1
      n1 = new SListNode<T>(elem);
      n1->initialize(elem, n0, header);
      n0->next_ = n1;
      header->prev_ = n1;
      length_++;
      return true;
   }

   // find the first list item that is greater/eq (>=) than insert-elem
   SListNode<T> *visit = n0;  // start at position zero node

   while (visit->isItemNode()) {
      T val = visit->element();
      if (val >= elem) {  // found location for insert
         break;
      }

      visit = visit->child();
   }

   if (visit->isHeadNode()) {  // looped entire list, so insert-elem is largest value
      // attach to tail end
      SListNode<T> *newNode = new SListNode<T>(elem);
      SListNode<T> *tn = tailNode();
      newNode->initialize(elem, tn, header);
      tn->next_ = newNode;
      header->prev_ = newNode;
   } else {
      if (elementMatch(visit, elem)) {  // duplicate already exists
         visit->counterPlus();          // increment the occurance counter
      } else {
         // attach in front of cursor (visit)
         SListNode<T> *newNode = new SListNode<T>(elem);
         SListNode<T> *parent = visit->parent();
         newNode->initialize(elem, parent, visit);
         parent->next_ = newNode;
         visit->prev_ = newNode;
      }
   }

   length_++;

   return true;
}

// node deletion
// accepts the element to search for removal as parameter.
// for duplicates, we only remove the first match (not every match).
template <typename T>
bool SortedList<T>::remove(T elem) {
   int index = elementIndex(elem);
   if (index == NODE_UNDEFINED) {
      return false;
   }

   SListNode<T> *visit = zeroNode();  // position cursor to zero node

   for (int i = 0; i < index; i++) {
      visit = visit->child();  // position cursor to child node
   }

   // TODO for duplicates, decrement counter instead of removing whole node

   deleteNode(visit);  // release node resources
   length_--;          // sync list length
   return true;
}

// List reset
// remove nodes starting at tail end
template <typename T>
void SortedList<T>::clear() {
   if (empty()) {
      return;
   }

   SListNode<T> *tmp;
   SListNode<T> *n = zeroNode();  // start with zero node
   while (n->isItemNode()) {
      tmp = n;          // bookmark the node
      n = n->child();   // advance cursor
      deleteNode(tmp);  // free node
   }

   length_ = 0;
   header->prev_ = nullptr;
   header->next_ = nullptr;
}

// find the node index of the element specified
// since locating the node by element is repeated, this may be reused.
template <typename T>
int SortedList<T>::elementIndex(T elem) {
   if (empty()) {
      return NODE_UNDEFINED;
   }

   int index = 0;
   SListNode<T> *visit = zeroNode();  // position cursor to zero node

   while (visit->isItemNode()) {
      if (elementMatch(visit, elem)) {
         break;  // found a matching element
      }

      visit = visit->child();  // position cursor to child node
      index++;                 // increment node index
   }

   if (visit->isHeadNode()) {
      // we looped through whole list, but no match
      return NODE_UNDEFINED;
   }

   return index;
}

// Assignment operator
template <typename T>
SortedList<T> &SortedList<T>::operator=(const SortedList<T> &right) {
   // check for self-assignment
   if (this == &right) {
      return *this;
   }

   length_ = right.length_;

   header = right.header->clone();
   return *this;
}

// Index operator
// calculation needed because we allow duplicates so the
// list _length_ can be greater than the physical nodes.
template <typename T>
T SortedList<T>::operator[](const int index) const {
   if (empty() || index < 0) {
      return safeNull<T>();
   }

   int max = size() - 1;  // zero-index means max is one less than length
   if (index > max) {
      return safeNull<T>();
   }

   int position = 0;
   SListNode<T> *visit = zeroNode();  // position cursor to zero node

   while (visit->isItemNode()) {
      if (index == position) {
         // arrived at the node for specified index
         break;
      }
      int dups = position + visit->counterTotal();
      if (index <= dups && index > position) {
         // arrived at the node that has dups at the index
         break;
      }

      visit = visit->child();  // position cursor to child node
      position++;              // TODO should increment by node's duplicateTotal
   }

   if (visit->isHeadNode()) {
      // we looped through whole list, but no match
      return safeNull<T>();
   }

   return visit->element();
}

// head node's prev pointer always indicates the tail node
template <typename T>
SListNode<T> *SortedList<T>::tailNode() {
   return header->prev_;
}

// head node's next pointer always indicates the first node (with index 0)
template <typename T>
SListNode<T> *SortedList<T>::zeroNode() const {
   return header->next_;
}

// size is the effective length
template <typename T>
int SortedList<T>::size() const {
   // To clarify, the effective length can be greater than the physical node count.
   return length_;
}

// empty returns true when zero-length list
template <typename T>
bool SortedList<T>::empty() const {
   return (length_ == 0);
}

// delete a list node
// for internal use by the clear() method (so fewer sanity checks)
// Accepts the pointer to the target node as parameter.
template <typename T>
void SortedList<T>::deleteNode(SListNode<T> *node) {
   // first detach (make into orphan)
   SListNode<T> *parent = node->parent();
   SListNode<T> *child = node->child();

   if (parent->isHeadNode() && child->isHeadNode()) {  // single node list
      header->next_ = nullptr;
      header->prev_ = nullptr;
   } else {
      child->prev_ = parent;
      parent->next_ = child;
   }

   node->next_ = nullptr;
   node->prev_ = nullptr;
   delete node;
}
/*
// TODO refactor this away? if while loops can always locate head now
template <typename T>
int SortedList<T>::indexMax() const {
   // physical nodes count

   if (empty()) {
      return 0;
   }

   int max = 0;
   SListNode<T> *visit = zeroNode();
   while (visit->isItemNode()) {
      visit = visit->child();
      max++;
   }
   return max;
}*/

////////////////////////////////////////////////
// Non-member overloads
//

// Print stream operator (see example from TICPP p.738)
template <typename T>
std::ostream &operator<<(std::ostream &os, const SortedList<T> &right) {
   if (right.empty()) {  // would "{EMPTY}" be too confusing?
      os << "" << std::endl;
      return os;
   }

   SListNode<T> *visit = right.zeroNode();

   while (visit->isItemNode()) {
      int dups = 1 + visit->counterTotal();
      T el = visit->element();
      for (int i = 0; i < dups; i++) {
         os << el << ", ";
      }
      visit = visit->child();
   }

   // TODO avoid hanging comma

   return os;
}
