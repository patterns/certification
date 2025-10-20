// SortedList.cpp; Hsin-ih Tu; 2025.10.16;
// Definition of sorted circular double linked list
//

// List constructor
template <typename T>
SortedList<T>::SortedList() {
   DListNode<T> *dummy = new DListNode<T>;
   dummy->initialize(NODE_HEAD, nullptr, nullptr);
   header_ = dummy;
   length_ = 0;
   traverseCount_ = 0;
}

// List deconstructor
template <typename T>
SortedList<T>::~SortedList() {
   clear();
   delete header_;
}

// List copy-constructor
// (implement pass and return by value)
template <typename T>
SortedList<T>::SortedList(const SortedList<T> &rhs) {
   header_ = rhs.header_->clone(rhs.length_);
   length_ = rhs.length_;
   traverseCount_ = rhs.traverseCount_;
}

// List length
template <typename T>
int SortedList<T>::getCurrentSize() const {
   return length_;
}

// List empty identity
template <typename T>
bool SortedList<T>::isEmpty() const {
   return (length_ == 0);
}

// List head identity
template <typename T>
bool SortedList<T>::isHeadNode(DListNode<T> *n) const {
   return (n->item_ == NODE_HEAD);
}

// Element identity
template <typename T>
bool SortedList<T>::elementMatch(DListNode<T> *n, T elem) const {
   return (n->item_ == elem);
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

   DListNode<T> *newNode = new DListNode<T>;

   switch (length_) {
      case 0: {  // the empty list
         // the head node's next/prev began as nullptr,
         // and new node's prev will point to the head
         newNode->initialize(elem, header_, header_);
         header_->next_ = newNode;
         header_->prev_ = newNode;
         break;
      }
      case 1: {                 // single node
         if (ADD_MODE_FRONT) {  // new nodes are added to the front
            DListNode<T> *n0 = zeroNode();
            newNode->initialize(elem, header_, n0);
            n0->prev_ = newNode;
            header_->next_ = newNode;

         } else {  // we add the new node by attaching to the tail
            DListNode<T> *n0 = zeroNode();
            newNode->initialize(elem, n0, header_);
            n0->next_ = newNode;
            header_->prev_ = newNode;
         }
         break;
      }
      default: {
         if (ADD_MODE_FRONT) {  // new nodes are added to the front
            DListNode<T> *n0 = zeroNode();
            newNode->initialize(elem, header_, n0);
            n0->prev_ = newNode;
            header_->next_ = newNode;

         } else {  // we add the new node by attaching to the tail
            DListNode<T> *tn = tailNode();
            newNode->initialize(elem, tn, header_);
            tn->next_ = newNode;
            header_->prev_ = newNode;
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
   DListNode<T> *visit = header_->next_;  // position cursor to zero node

   for (int i = 0; i < index; i++) {
      visit = visit->next_;  // position cursor to child node
      total++;               // track traversal/visits
   }

   deleteNode(visit);  // release node resources
   length_--;          // sync list length
   return true;
}

// List reset
// we avoid traversal by using the tail pointer
template <typename T>
void SortedList<T>::clear() {
   switch (length_) {
      case 0: {
         return;
      }
      case 1: {
         deleteNode(header_->next_);
         break;
      }
      default: {
         for (int i = length_; i > 0; i--) {
            DListNode<T> *tn = tailNode();
            deleteNode(tn);
         }
      }
   }

   length_ = 0;
   resetTraverseCount();
   header_->prev_ = nullptr;
   header_->next_ = nullptr;
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
   if (isEmpty() || elem < 0) {
      return NODE_UNDEFINED;
   }
   int index = 0;
   int total = 0;
   DListNode<T> *visit = zeroNode();  // position cursor to zero node

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
// see TICPP, Bruce Eckel for reference
// in the same way that we need to implement the copy-constructor,
// we must write the operator because we use dynamic allocation.
template <typename T>
SortedList<T> &SortedList<T>::operator=(const SortedList<T> &right) {
   // check for self-assignment
   if (this == &right) {
      return *this;
   }

   length_ = right.length_;
   traverseCount_ = right.traverseCount_;
   header_ = right.header_->clone(right.length_);
   return *this;
}

// Index operator
template <typename T>
T SortedList<T>::operator[](const int index) {

   if (isEmpty() || index < 0) {
      return ERROR_INDEX;
   }

   int max = size();    // zero-index means largest is one less than total
   if (index > (max - 1)) {
      return ERROR_INDEX;
   }

   int total = 0;
   DListNode<T> *visit = zeroNode();  // position cursor to zero node

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
      return NODE_UNDEFINED;
   }

   return visit->item_;
}

// Traverse count mathematical addition
template <typename T>
void SortedList<T>::traversePlus(int val) {
   traverseCount_ += val;
}

// head node's prev pointer always indicates the tail node
template <typename T>
DListNode<T> *SortedList<T>::tailNode() {
   return header_->prev_;
}

// head node's next pointer always indicates the first node (with index 0)
template <typename T>
DListNode<T> *SortedList<T>::zeroNode() const {
   return header_->next_;
}

// size returns the node count (length)
template <typename T>
int SortedList<T>::size() const {
   return length_;
}

// delete a list node and free resources
// for use by the clear() method, and the contains() in the overridden versions to achieve swapping.
// Accepts the pointer to the target node as parameter.
template <typename T>
void SortedList<T>::deleteNode(DListNode<T> *node) {
   switch (length_) {
      case 0: {
         // empty list, unreachable?
         return;
      }
      case 1: {
         // single node list
         header_->next_ = nullptr;
         header_->prev_ = nullptr;
         break;
      }
      default: {
         // first detach (make into orphan)
         DListNode<T> *parent = node->prev_;
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
std::ostream& operator<<(std::ostream& os, const SortedList<T>& right) {
   DListNode<T> *visit = right.zeroNode();

   for (int i=0; i < right.size(); i++) {
      os << visit->item_ << ", ";
      visit = visit->child();
   }

   // TODO avoid hanging comma
   // TODO is empty line expected for empty list?

   return os;
}

////////////////////////////////////////////////
// DListNode members
//

// node initialization (see TICPP, Bruce Eckel)
template <typename T>
void DListNode<T>::initialize(T elem, DListNode<T> *prev, DListNode<T> *next) {
   item_ = elem;
   prev_ = prev;
   next_ = next;
}

// copy the nodes meant to be called by the header_ node
template <typename T>
DListNode<T> *DListNode<T>::clone(const int length) const {
   // make the head copy
   DListNode *dummy = new DListNode;
   dummy->initialize(NODE_HEAD, nullptr, nullptr);

   if (item_ != NODE_HEAD) {  // expect to be called by header_ node
      return dummy;           // probably should throw exception here.....
   }

   switch (length) {
      case 0: {  // empty list
         break;
      }
      case 1: {  // single node
         DListNode<T> *tail = parent();
         DListNode<T> *newNode = new DListNode<T>;
         newNode->item_ = tail->item_;  // copy item
         newNode->next_ = dummy;        // circular link from tail
         newNode->prev_ = dummy;        // link child to head
         dummy->next_ = newNode;        // link head to child
         dummy->prev_ = newNode;        // circular link to tail
         break;
      }
      default: {
         DListNode<T> *bookmark;

         // make the node copies starting with tail (reverse)
         DListNode<T> *visit = parent();
         DListNode<T> *newNode = new DListNode<T>;

         newNode->item_ = visit->item_;  // copy tail
         newNode->next_ = dummy;         // link tail to head
         newNode->prev_ = nullptr;       // placeholder for parent to tail
         dummy->prev_ = newNode;         // link head to tail

         bookmark = newNode;       // bookmark the child
         visit = visit->parent();  // position cursor to the parent of tail

         // non-tail nodes
         for (int i = 1; i < length; i++) {
            newNode = new DListNode<T>;
            bookmark->prev_ = newNode;      // link child to new parent
            newNode->item_ = visit->item_;  // copy item
            newNode->next_ = bookmark;      // link parent to child
            newNode->prev_ = nullptr;       // placeholder (for new node)
            bookmark = newNode;             // bookmark the child
            visit = visit->parent();        // decrement cursor
         }

         bookmark->prev_ = dummy;  // link zero node to head
         dummy->next_ = newNode;   // link head to zero node
      }
   }

   return dummy;
}

// next pointer getter
template <typename T>
DListNode<T> *DListNode<T>::child() const {
   return next_;
}

// previous pointer getter
template <typename T>
DListNode<T> *DListNode<T>::parent() const {
   return prev_;
}
