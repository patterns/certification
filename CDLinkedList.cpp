// CDLinkedList.cpp; Hsin-ih Tu; 2025.10.07;
// circular double linked list
//

#include "CDLinkedList.h"

// List constructor
CDLinkedList::CDLinkedList() {
   DListNode *dummy = new DListNode;
   dummy->initialize(NODE_HEAD, nullptr, nullptr);
   header_ = dummy;
   length_ = 0;
   traverseCount_ = 0;
}

// List deconstructor
CDLinkedList::~CDLinkedList() {
   clear();
   delete header_;
}

// List copy-constructor
// (implement pass and return by value)
CDLinkedList::CDLinkedList(const CDLinkedList &rhs) {
   header_ = rhs.header_->clone(rhs.length_);
   length_ = rhs.length_;
   traverseCount_ = rhs.traverseCount_;
}

// List length
int CDLinkedList::getCurrentSize() const { return length_; }

// List empty identity
bool CDLinkedList::isEmpty() const { return (length_ == 0); }

// List head identity
bool CDLinkedList::isHeadNode(DListNode *n) const { return (n->item_ == NODE_HEAD); }

// Element identity
bool CDLinkedList::elementMatch(DListNode *n, int elem) const { return (n->item_ == elem); }

// node creation
// Requirement states "add to front".
// The traverse count is expected to be updated. Which can be achieved
// via an internal call to contains() or another method that concentrates
// traversals. The internal call benefits overridden versions because
// the count will be managed already.
bool CDLinkedList::add(int elem) {
   if (elem < 0) {
      return false;  // forbid negative values
   }

   if (contains(elem)) {
      return true;  // duplicates are ignored according to requirement
   }

   DListNode *newNode = new DListNode;

   switch (length_) {
      case 0: {  // the empty list
         // the head node's next/prev began as nullptr,
         // and new node's prev will point to the head
         newNode->initialize(elem, header_, header_);
         header_->next_ = newNode;
         header_->prev_ = newNode;
         break;
      }
      case 1: {  // single node
         if (ADD_MODE_FRONT) {  // new nodes are added to the front
            DListNode *n0 = zeroNode();
            newNode->initialize(elem, header_, n0);
            n0->prev_ = newNode;
            header_->next_ = newNode;

         } else {   // we add the new node by attaching to the tail
            DListNode *n0 = zeroNode();
            newNode->initialize(elem, n0, header_);
            n0->next_ = newNode;
            header_->prev_ = newNode;
         }
         break;
      }
      default: {
         if (ADD_MODE_FRONT) {  // new nodes are added to the front
            DListNode *n0 = zeroNode();
            newNode->initialize(elem, header_, n0);
            n0->prev_ = newNode;
            header_->next_ = newNode;

         } else {   // we add the new node by attaching to the tail
            DListNode *tn = tailNode();
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
bool CDLinkedList::remove(int elem) {
   int index = elementIndex(elem);
   if (index == NODE_UNDEFINED) {
      return false;
   }

   int total = 0;
   DListNode *visit = header_->next_;  // position cursor to zero node

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
void CDLinkedList::clear() {
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
            DListNode *tn = tailNode();
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
bool CDLinkedList::contains(int elem) {
   int index = elementIndex(elem);
   if (index == NODE_UNDEFINED) {
      return false;
   }

   return true;
}

// find the node index of the element specified
// since locating the node by element is repeated, this may be reused.
int CDLinkedList::elementIndex(int elem) {
   if (isEmpty() || elem < 0) {
      return NODE_UNDEFINED;
   }
   int index = 0;
   int total = 0;
   DListNode *visit = zeroNode();  // position cursor to zero node

   while (!isHeadNode(visit)) {
      if (elementMatch(visit, elem)) {
         break;  // found a matching element
      }
      visit = visit->child();  // position cursor to child node
      total++;               // track traversal/visits
      index++;               // increment node index
   }

   traversePlus(total);  // store traversals

   if (isHeadNode(visit)) {
      // we looped through whole list, but no match
      return NODE_UNDEFINED;
   }

   return index;
}

// List index access
// Primarily used to display the state of the list.
// So there is some discussion about whether the traverse count
// should be updated or not. For now, we do updates to the count
// (until we can think of a simple approach to dump or to-string).
// IDEA, maybe use a copy by passing the list into an internal function?
int CDLinkedList::retrieve(const int index) {
   if (isEmpty() || index < 0 || index > length_) {
      return ERROR_INDEX;
   }

   int total = 0;
   DListNode *visit = zeroNode();  // position cursor to zero node

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

// Traverse count getter
int CDLinkedList::getTraverseCount() const { return traverseCount_; }

// Traverse count reset
void CDLinkedList::resetTraverseCount() { traverseCount_ = 0; }

// Assignment operator
// see TICPP, Bruce Eckel for reference
// in the same way that we need to implement the copy-constructor,
// we must write the operator because we use dynamic allocation.
CDLinkedList &CDLinkedList::operator=(const CDLinkedList &right) {
   // check for self-assignment
   if (this == &right) {
      return *this;
   }

   length_ = right.length_;
   traverseCount_ = right.traverseCount_;
   header_ = right.header_->clone(right.length_);
   return *this;
}

// Traverse count mathematical addition
void CDLinkedList::traversePlus(int val) { traverseCount_ += val; }

// head node's prev pointer always indicates the tail node
DListNode *CDLinkedList::tailNode() { return header_->prev_; }

// head node's next pointer always indicates the first node (with index 0)
DListNode *CDLinkedList::zeroNode() { return header_->next_; }

// delete a list node and free resources
// for use by the clear() method, and the contains() in the overridden versions to achieve swapping.
// Accepts the pointer to the target node as parameter.
void CDLinkedList::deleteNode(DListNode *node) {
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
         DListNode *parent = node->prev_;
         node->next_->prev_ = parent;
         parent->next_ = node->next_;
      }
   }

   node->next_ = nullptr;
   node->prev_ = nullptr;
   delete node;
}

////////////////////////////////////////////////
// DListNode members
//

// node initialization (see TICPP, Bruce Eckel)
void DListNode::initialize(int elem, DListNode *prev, DListNode *next) {
   item_ = elem;
   prev_ = prev;
   next_ = next;
}

// copy the nodes meant to be called by the header_ node
DListNode *DListNode::clone(const int length) const {
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
         DListNode *tail = parent();
         DListNode *newNode = new DListNode;
         newNode->item_ = tail->item_;  // copy item
         newNode->next_ = dummy;        // circular link from tail
         newNode->prev_ = dummy;        // link child to head
         dummy->next_ = newNode;        // link head to child
         dummy->prev_ = newNode;        // circular link to tail
         break;
      }
      default: {
         DListNode *bookmark;

         // make the node copies starting with tail (reverse)
         DListNode *visit = parent();
         DListNode *newNode = new DListNode;

         newNode->item_ = visit->item_;  // copy tail
         newNode->next_ = dummy;         // link tail to head
         newNode->prev_ = nullptr;       // placeholder for parent to tail
         dummy->prev_ = newNode;         // link head to tail

         bookmark = newNode;       // bookmark the child
         visit = visit->parent();  // position cursor to the parent of tail

         // non-tail nodes
         for (int i = 1; i < length; i++) {
            newNode = new DListNode;
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
DListNode *DListNode::child() const { return next_; }

// previous pointer getter
DListNode *DListNode::parent() const { return prev_; }
