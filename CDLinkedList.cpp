// CDLinkedList.cpp; Hsin-ih Tu; 2025.10.07;
// circular double linked list
//

#include "CDLinkedList.h"
/***********
////#include <algorithm>
************/

void DListNode::initialize(int elem, DListNode *prev, DListNode *next) {
   item_ = elem;
   prev_ = prev;
   next_ = next;
}

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
   ////clear();
}

// ctor initialized with values from parameter list
CDLinkedList::CDLinkedList(const CDLinkedList &rhs) {
   // TODO
}

// List length
int CDLinkedList::getCurrentSize() const { return length_; }
/******
int CDLinkedList::getCurrentSize() const {
   int total = 0;
   DListNode *visit = header_->next_;

   // empty list
   if (visit == nullptr) {
      return 0;
   }

   // access element
   while (visit->item_ != NODE_HEAD) {
      visit = visit->next_;
      total++;
   }

   return total;
}**********/

// List empty identity
bool CDLinkedList::isEmpty() const {
   if (length_ == 0) {
      return true;
   }
   return false;
}

// node creation
bool CDLinkedList::add(int elem) {
   if (elem < 0) {
      // don't allow negative numbers
      return false;
   }

   DListNode *newZero = new DListNode;
   newZero->initialize(elem, header_, header_->next_);

   if (header_->next_ == nullptr) {
      // began as empty list, enable circular link
      header_->prev_ = newZero;
   } else {
      // reassign the previous pointer of the (old) zeroth node
      header_->next_->prev_ = newZero;
   }

   header_->next_ = newZero;
   indexToPointer_[length_] = newZero;
   length_++;

   return true;
}

// node deletion
bool CDLinkedList::remove(int value) { return false; }

// List reset
void CDLinkedList::clear() {
   if (isEmpty()) {
      return;
   }

   DListNode *current = header_->next_;
   while (current->item_ != NODE_HEAD) {
      DListNode *tmp = current;
      current = current->next_;
      tmp->next_ = nullptr;
      tmp->prev_ = nullptr;
      delete tmp;
   }

   delete header_;
}

// node membership
bool CDLinkedList::contains(int target) { return false; }

// List index access
int CDLinkedList::retrieve(const int index) const {
   if (index < 0 || index > length_) {
      return ERROR_INDEX;
   }

   DListNode *node = indexToPointer_[index];
   if (node == nullptr) {
      return NODE_UNDEFINED;
   }
   return node->item_;
}

// Traverse count getter
int CDLinkedList::getTraverseCount() const { return 0; }

// Traverse count reset
void CDLinkedList::resetTraverseCount() { traverseCount_ = 0; }
