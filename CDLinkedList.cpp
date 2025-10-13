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

// ctor initialized with values from parameter list
CDLinkedList::CDLinkedList(const CDLinkedList &rhs) {
   // TODO
}

// List length
int CDLinkedList::getCurrentSize() const { return length_; }

// List empty identity
bool CDLinkedList::isEmpty() const { return (length_ == 0); }

// node creation
bool CDLinkedList::add(int elem) {
   if (elem < 0) {
      // don't allow negative numbers
      return false;
   }
   if (contains(elem)) {
      // don't allow duplicate numbers
      return false;
   }

   DListNode *newNode = new DListNode;

   if (length_ == 0) {  // the empty list
      // the head node's next/prev began as nullptr,
      // and new node's prev will point to the head
      newNode->initialize(elem, header_, header_);
      header_->next_ = newNode;
      header_->prev_ = newNode;
   } else if (length_ == 1) {  // one node list
      DListNode *n0 = header_->next_;
      newNode->initialize(elem, n0, header_);
      n0->next_ = newNode;
      header_->prev_ = newNode;
   } else {
      // we add new node by attaching to the tail
      DListNode *tn = tailNode();
      newNode->initialize(elem, tn, header_);
      tn->next_ = newNode;
      header_->prev_ = newNode;
   }

   length_++;

   return true;
}

// node deletion
// accepts the element to search for removal as paramter.
// assume no duplicate list elements.
bool CDLinkedList::remove(int elem) {
   if (isEmpty() || elem < 0) {
      return false;
   }

   int total = 0;
   DListNode *visit = header_->next_;

   while (visit->item_ != NODE_HEAD) {
      // access element
      if (visit->item_ == elem) {
         // found a matching element
         break;
      }
      visit = visit->next_;
      // track traversal/visits
      total++;
   }

   // store traversals
   traverseCount_ += total;

   if (visit->item_ == elem) {
      deleteNode(visit);
      length_--;
      return true;
   }

   return false;
}

// List reset
// we avoid traversal by using the tail pointer
void CDLinkedList::clear() {
   if (length_ == 0) {
      return;
   } else if (length_ == 1) {
      deleteNode(header_->next_);
   } else {
      for (int i = length_; i > 0; i--) {
         DListNode *tn = tailNode();
         deleteNode(tn);
      }
   }

   length_ = 0;
   resetTraverseCount();
   header_->prev_ = nullptr;
   header_->next_ = nullptr;
}

// node membership
bool CDLinkedList::contains(int elem) {
   if (isEmpty() || elem < 0) {
      return false;
   }

   int total = 0;
   DListNode *visit = header_->next_;

   while (visit->item_ != NODE_HEAD) {
      visit = visit->next_;
      // track traversal/visits
      total++;
      // access element
      if (visit->item_ == elem) {
         // found a matching element
         break;
      }
   }

   // store traversals
   traverseCount_ += total;

   if (visit->item_ == NODE_HEAD) {
      // we looped through whole list, but no match
      return false;
   }
   return true;
}

// List index access
// since calling contains() incurs traversals, should we just loop through
// because it would be twice the work?
int CDLinkedList::retrieve(const int index) {
   if (isEmpty() || index < 0 || index > length_) {
      return ERROR_INDEX;
   }

   int total = 0;
   DListNode *visit = header_->next_;

   while (visit->item_ != NODE_HEAD) {
      // access element
      if (index == total) {
         // found node at index
         break;
      }
      visit = visit->next_;
      // track traversal/visits
      total++;
   }

   // store traversals
   traverseCount_ = traverseCount_ + total;

   if (visit->item_ == NODE_HEAD) {
      // we looped through whole list, but no match
      return NODE_UNDEFINED;
   }

   return visit->item_;
}

// Traverse count getter
int CDLinkedList::getTraverseCount() const { return traverseCount_; }

// Traverse count reset
void CDLinkedList::resetTraverseCount() { traverseCount_ = 0; }

// head node's prev pointer always indicates the tail node
DListNode *CDLinkedList::tailNode() { return header_->prev_; }

// delete a list node and free resources
// for use by the clear() method.
// accepts the pointer to the target node as parameter.
void CDLinkedList::deleteNode(DListNode *node) {
   if (length_ == 0) {
      // empty list, unreachable?
      return;
   } else if (length_ == 1) {
      // single node list
      header_->next_ = nullptr;
      header_->prev_ = nullptr;
   } else {
      // first detach (make into orphan)
      DListNode *parent = node->prev_;
      node->next_->prev_ = parent;
      parent->next_ = node->next_;
   }

   node->next_ = nullptr;
   node->prev_ = nullptr;
   delete node;
}

// node initialization (see TIC )
void DListNode::initialize(int elem, DListNode *prev, DListNode *next) {
   item_ = elem;
   prev_ = prev;
   next_ = next;
}
