// CDLinkedList.cpp; Hsin-ih Tu; 2025.10.07;
// circular double linked list
//

#include "CDLinkedList.h"
/***********
////#include <algorithm>

const int LIST_CAPACITY = (1024 - 1);
const int NODE_HEAD = -99;
const int NODE_UNKNOWN = -100;
const int ERROR_INDEX = -101;
************/
// List constructor
CDLinkedList::CDLinkedList() {
   header_ = new DListNode;
   header_->next = nullptr;
   header_->prev = nullptr;
   header_->item = NODE_HEAD;
}

// List deconstructor
CDLinkedList::~CDLinkedList() {
   // TODO
}

// ctor initialized with values from parameter list
CDLinkedList::CDLinkedList(const CDLinkedList &rhs) {
   // TODO
}

// List length
int CDLinkedList::getCurrentSize() const { return 0; }

// List empty identity
bool CDLinkedList::isEmpty() const { return true; }

// node creation
bool CDLinkedList::add(int value) { return false; }

// node deletion
bool CDLinkedList::remove(int value) { return false; }

// List reset
void CDLinkedList::clear() {
   // TODO
}

// node membership
bool CDLinkedList::contains(int target) { return false; }

// List index access
int CDLinkedList::retrieve(const int index) const {
   // TODO length is dynamically alloc
   if (index < 0 || index > LIST_CAPACITY) {
      return ERROR_INDEX;
   }

   // TODO
   return NODE_UNDEFINED;
}

// Traverse count getter
int CDLinkedList::getTraverseCount() const { return 0; }

// Traverse count reset
void CDLinkedList::resetTraverseCount() { traverseCount_ = 0; }
