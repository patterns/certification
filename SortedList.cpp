// SortedList.cpp; Hsin-ih Tu; 2025.10.16;
// Definition of sorted circular double linked list
//

// List constructor
template <typename T>
SortedList<T>::SortedList():
   length_(0),
   destroying_(false),
   header(new SListNode<T>(HeadNode, true)) {
}

// List deconstructor
template <typename T>
SortedList<T>::~SortedList() {
   if (destroying_) {    // check whether already being destroyed
      return;
   }

   destroying_ = true;    // set flag for destroy stage
   clear();
   delete header;
   header = nullptr;
}

// List copy-constructor
template <typename T>
SortedList<T>::SortedList(const SortedList<T> &other):
   length_(other.length_),
   header(other.header->clone()) {
}

// Move-constructor
template <typename T>
SortedList<T>::SortedList(SortedList<T> &&other):
   length_(0),
   header(nullptr) {
   // using our move assignment operator to achieve move constructor.
   // See the tutorial
   // https://learn.microsoft.com/en-us/cpp/cpp/move-constructors-and-move-assignment-operators-cpp?view=msvc-170
   *this = std::move(other);
}

// node creation
template <typename T>
bool SortedList<T>::insert(const T &elem) {
   if (empty()) {  // empty list
      SListNode<T> *newNode = new SListNode<T>(elem);
      newNode->initialize(elem, header, header);
      header->next_ = newNode;
      header->prev_ = newNode;
      length_++;
      return true;
   }

   SListNode<T> *n0 = zeroNode();

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
      if (visit->elementMatch(elem)) {  // duplicate already exists
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
template <typename T>
void SortedList<T>::clear() {
   if (empty()) {    // already empty
      return;
   }

   SListNode<T> *tmp;
   SListNode<T> *n = zeroNode();  // start with zero node
   while (n->isItemNode()) {
      tmp = n;          // bookmark the node
      n = n->child();   // advance cursor
      deleteNode(tmp);  // free node
      tmp = nullptr;
   }

   length_ = 0;
   header->prev_ = nullptr;
   header->next_ = nullptr;
}

// find the node index of the element specified
// TODO no longer reused, so change this to binary search?
template <typename T>
int SortedList<T>::elementIndex(T elem) {
   if (empty()) {
      return NODE_UNDEFINED;
   }

   int index = 0;
   SListNode<T> *visit = zeroNode();  // position cursor to zero node

   while (visit->isItemNode()) {
      if (visit->elementMatch(elem)) {
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

// Assignment-copy operator
template <typename T>
SortedList<T> &SortedList<T>::operator=(const SortedList<T> &right) {
   if (this == &right) {    // check for self-assignment
      return *this;
   }

   clear();    // Free existing nodes.
   delete header;    // Free exisitng head.

   length_ = right.length_;
   header = right.header->clone();

   return *this;
}

// Assignment-move operator
template <typename T>
SortedList<T> &SortedList<T>::operator=(SortedList<T> &&other) {
   if (this == &other) {    // check for self-assignment
      return *this;
   }

   clear();    // Free existing nodes.
   delete header;    // Free existing head.

   length_ = other.length_;
   header = other.header;    // Move the head from the source obj.

   other.length_ = 0;
   other.header = nullptr;    // Release the pointer from the source obj.

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

// List append operator
template <typename T>
SortedList<T> SortedList<T>::operator+(const SortedList<T> &other) {
   // merge l1 and l2 into new (sorted) list
   // - declare return list variable (lv)
   // - copy l2 into lv 
   // - insert l1 items into lv 

   if (this->empty()) {    // l1 is empty, just copy l2
      return SortedList<T>(other);
   }

   if (other.empty()) {    // l2 is empty, just copy l1
      return SortedList<T>(*this);
   }

   SortedList<T> lv(other);    // copy l2

   SListNode<T> *visit = zeroNode();    // start cursor at l1's zero node

   while (visit->isItemNode()) {
      lv.insert(visit->element());    // insert item from l1 into temp list
      visit = visit->child();
   }

   return SortedList<T>(lv);    // return a copy of the (local) list result
}

// List equals operator
template <typename T>
bool SortedList<T>::operator==(const SortedList<T> &other) const {
   if (this == &other) {    // check for identity
      return true;
   }

   if (empty() && other.empty()) {    // check for empty identity
      return true;
   }

   if (length_ != other.length_) {    // both must be same size
      return false;
   }

   SListNode<T> *curr = zeroNode();
   SListNode<T> *visit = other.zeroNode();

   while (visit->isItemNode() && curr->isItemNode()) {
      T el = curr->element();
      if (!visit->elementMatch(el)) {    // both items must be equal
         return false;
      }

      curr = curr->child();
      visit = visit->child();
   }

   return true;
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

   delete node;
}

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
