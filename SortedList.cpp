// SortedList.cpp; Hsin-ih Tu; 2025.10.16;
// Definition of sorted circular double linked list
//

// List constructor
template <typename T>
SortedList<T>::SortedList() {
   SListNode<T> *dummy = new SListNode<T>(HeadNode, true);
   ////dummy->initialize(NODE_HEAD, nullptr, nullptr);
   ////dummy->ntype_ = HeadNode;
   dummy->next_ = nullptr;
   dummy->prev_ = nullptr;
   header = dummy;
   length_ = 0;
   traverseCount_ = 0;
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
   header = rhs.header->clone(rhs.length_);
   length_ = rhs.length_;
   traverseCount_ = rhs.traverseCount_;
}

// List head identity
template <typename T>
bool SortedList<T>::isHeadNode(SListNode<T> *n) const {
   return n->isHeadNode();
}

// Element identity
template <typename T>
bool SortedList<T>::elementMatch(SListNode<T> *n, T elem) const {
   return n->elementMatch(elem);
}

// node creation
// Requirement states "add to front".
// The traverse count is expected to be updated. Which can be achieved
// via an internal call to contains() or another method that concentrates
// traversals. The internal call benefits overridden versions because
// the count will be managed already.
template <typename T>
bool SortedList<T>::add(T elem) {
   if (elem < 0) {
      return false;  // forbid negative values
   }

   if (contains(elem)) {
      return true;  // duplicates are ignored according to requirement
   }

   SListNode<T> *newNode = new SListNode<T>(elem);

   switch (length_) {
      case 0: {  // the empty list
         // the head node's next/prev began as nullptr,
         // and new node's prev will point to the head
         newNode->initialize(elem, header, header);
         header->next_ = newNode;
         header->prev_ = newNode;
         break;
      }
      case 1: {                 // single node
         if (ADD_MODE_FRONT) {  // new nodes are added to the front
            SListNode<T> *n0 = zeroNode();
            newNode->initialize(elem, header, n0);
            n0->prev_ = newNode;
            header->next_ = newNode;

         } else {  // we add the new node by attaching to the tail
            SListNode<T> *n0 = zeroNode();
            newNode->initialize(elem, n0, header);
            n0->next_ = newNode;
            header->prev_ = newNode;
         }
         break;
      }
      default: {
         if (ADD_MODE_FRONT) {  // new nodes are added to the front
            SListNode<T> *n0 = zeroNode();
            newNode->initialize(elem, header, n0);
            n0->prev_ = newNode;
            header->next_ = newNode;

         } else {  // we add the new node by attaching to the tail
            SListNode<T> *tn = tailNode();
            newNode->initialize(elem, tn, header);
            tn->next_ = newNode;
            header->prev_ = newNode;
         }
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

   int total = 0;
   SListNode<T> *visit = zeroNode();  // position cursor to zero node

   for (int i = 0; i < index; i++) {
      visit = visit->child();  // position cursor to child node
      total++;                 // track traversal/visits
   }

   deleteNode(visit);  // release node resources
   length_--;          // sync list length
   return true;
}

// List reset
// remove nodes starting at tail end
template <typename T>
void SortedList<T>::clear() {
   switch (length_) {
      case 0: {
         return;
      }
      case 1: {
         deleteNode(zeroNode());
         break;
      }
      default: {
         for (int i = length_; i > 0; i--) {
            SListNode<T> *tn = tailNode();
            deleteNode(tn);
         }
      }
   }

   length_ = 0;
   resetTraverseCount();
   header->prev_ = nullptr;
   header->next_ = nullptr;
}

// node membership
// The traverse count is expected to be updated. Which can be achieved
// via an internal method that concentrates
// traversals. The internal call benefits overridden versions because
// the count will be managed already.
template <typename T>
bool SortedList<T>::contains(T elem) {
   int index = elementIndex(elem);
   if (index == NODE_UNDEFINED) {
      return false;
   }

   return true;
}

// find the node index of the element specified
// since locating the node by element is repeated, this may be reused.
template <typename T>
int SortedList<T>::elementIndex(T elem) {
   if (empty() || elem < 0) {
      return NODE_UNDEFINED;
   }
   int index = 0;
   int total = 0;
   SListNode<T> *visit = zeroNode();  // position cursor to zero node

   while (!isHeadNode(visit)) {
      if (elementMatch(visit, elem)) {
         break;  // found a matching element
      }
      visit = visit->child();  // position cursor to child node
      total++;                 // track traversal/visits
      index++;                 // increment node index
   }

   traversePlus(total);  // store traversals

   if (isHeadNode(visit)) {
      // we looped through whole list, but no match
      return NODE_UNDEFINED;
   }

   return index;
}

// Traverse count getter
template <typename T>
int SortedList<T>::getTraverseCount() const {
   return traverseCount_;
}

// Traverse count reset
template <typename T>
void SortedList<T>::resetTraverseCount() {
   traverseCount_ = 0;
}

// Assignment operator
template <typename T>
SortedList<T> &SortedList<T>::operator=(const SortedList<T> &right) {
   // check for self-assignment
   if (this == &right) {
      return *this;
   }

   length_ = right.length_;
   traverseCount_ = right.traverseCount_;
   header = right.header->clone(right.length_);
   return *this;
}

// Index operator
template <typename T>
T SortedList<T>::operator[](const int index) {
   if (empty() || index < 0) {
      return NULL;
   }

   int max = size() - 1;  // zero-index means max is one less than length
   if (index > max) {
      return NULL;
   }

   int total = 0;
   SListNode<T> *visit = zeroNode();  // position cursor to zero node

   while (!isHeadNode(visit)) {
      if (index == total) {
         // arrived at the node for specified index
         break;
      }

      visit = visit->child();  // position cursor to child node
      total++;                 // track traversal/visits
   }

   traversePlus(total);  // store traversals

   if (isHeadNode(visit)) {
      // we looped through whole list, but no match
      return NULL;
   }

   return visit->element();
}

// Traverse count mathematical addition
template <typename T>
void SortedList<T>::traversePlus(int val) {
   traverseCount_ += val;
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

// size returns the node count (length)
template <typename T>
int SortedList<T>::size() const {
   return length_;
}

// empty returns true when size is zero
template <typename T>
bool SortedList<T>::empty() const {
   return (length_ == 0);
}

// delete a list node and free resources
// for use by the clear() method, and the contains() in the overridden versions to achieve swapping.
// Accepts the pointer to the target node as parameter.
template <typename T>
void SortedList<T>::deleteNode(SListNode<T> *node) {
   switch (length_) {
      case 0: {
         // empty list, unreachable?
         return;
      }
      case 1: {
         // single node list
         header->next_ = nullptr;
         header->prev_ = nullptr;
         break;
      }
      default: {
         // first detach (make into orphan)
         SListNode<T> *parent = node->prev_;
         node->next_->prev_ = parent;
         parent->next_ = node->next_;
      }
   }

   node->next_ = nullptr;
   node->prev_ = nullptr;
   delete node;
}

////////////////////////////////////////////////
// Non-member overloads
//

// Print stream operator (see example from TICPP p.738)
template <typename T>
std::ostream &operator<<(std::ostream &os, const SortedList<T> &right) {
   SListNode<T> *visit = right.zeroNode();

   for (int i = 0; i < right.size(); i++) {
      os << visit->element() << ", ";
      visit = visit->child();
   }

   // TODO avoid hanging comma
   // TODO is empty line expected for empty list?

   return os;
}
