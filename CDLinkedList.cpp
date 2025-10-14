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
CDLinkedList::CDLinkedList(const CDLinkedList &cdl) {
   // make the head copy
   DListNode *dummy = new DListNode;
   dummy->initialize(NODE_HEAD, nullptr, nullptr);
   header_ = dummy;
   length_ = cdl.length_;
   traverseCount_ = cdl.traverseCount_;

   switch (cdl.length_) {
      case 0: {  // empty list
         break;
      }
      case 1: {  // single node
         DListNode *tail = cdl.header_->prev_;
         DListNode *newNode = new DListNode;
         newNode->item_ = tail->item_;                      // copy item
         newNode->next_ = header_;                          // circular link from tail
         newNode->prev_ = header_;                          // link child to head
         header_->next_ = newNode;                          // link head to child
         header_->prev_ = newNode;                          // circular link to tail
         break;
      }
      default: {
         DListNode *bookmark;

         // make the node copies starting with tail (reverse)
         DListNode *visit = cdl.header_->prev_;
         DListNode *newNode = new DListNode;

         newNode->item_ = visit->item_;                     // copy tail
         newNode->next_ = header_;                          // link tail to head
         newNode->prev_ = nullptr;                          // placeholder for parent to tail
         header_->prev_ = newNode;                          // link head to tail

         bookmark = newNode;                                // bookmark the child
         visit = visit->prev_;                              // position cursor to the parent of tail

         // non-tail nodes
         for (int i = 1; i < cdl.length_; i++) {
            newNode = new DListNode;
            bookmark->prev_ = newNode;                      // link child to new parent
            newNode->item_ = visit->item_;                  // copy item
            newNode->next_ = bookmark;                      // link parent to child
            newNode->prev_ = nullptr;                       // placeholder (for new node)
            bookmark = newNode;                             // bookmark the child
            visit = visit->prev_;                           // decrement cursor
         }

         bookmark->prev_ = header_;                         // link zero node to head
         header_->next_ = newNode;                          // link head to zero node
      }
   }
}

// List length
int CDLinkedList::getCurrentSize() const { return length_; }

// List empty identity
bool CDLinkedList::isEmpty() const { return (length_ == 0); }

// node creation (TODO requirement states "add to front")
// internal call to contains() because it will be overridden
bool CDLinkedList::add(int elem) {
   if (elem < 0) {
      return false;                                         // forbid negative values
   }

   if (contains(elem)) {
      return true;                                          // duplicates are ignored according to requirement
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
      case 1: {  // single node list
         DListNode *n0 = header_->next_;
         newNode->initialize(elem, n0, header_);
         n0->next_ = newNode;
         header_->prev_ = newNode;
         break;
      }
      default: {
         // we add the new node by attaching to the tail
         DListNode *tn = tailNode();
         newNode->initialize(elem, tn, header_);
         tn->next_ = newNode;
         header_->prev_ = newNode;
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
   DListNode *visit = header_->next_;                       // position cursor to zero node

   for (int i = 0; i < index; i++) {
      visit = visit->next_;                                 // position cursor to child node
      total++;                                              // track traversal/visits
   }

   deleteNode(visit);                                       // release node resources
   length_--;                                               // sync list length
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
   DListNode *visit = header_->next_;                       // position cursor to zero node

   while (visit->item_ != NODE_HEAD) {
      if (visit->item_ == elem) {
         break;                                             // found a matching element
      }
      visit = visit->next_;                                 // position cursor to child node
      total++;                                              // track traversal/visits
      index++;                                              // increment node index
   }

   traverseCount_ += total;                                 // store traversals

   if (visit->item_ == NODE_HEAD) {
      // we looped through whole list, but no match
      return NODE_UNDEFINED;
   }

   return index;
}

// List index access
// since calling contains() incurs traversals, should we just loop through
int CDLinkedList::retrieve(const int index) {
   if (isEmpty() || index < 0 || index > length_) {
      return ERROR_INDEX;
   }

   int total = 0;
   DListNode *visit = header_->next_;                       // position cursor to zero node

   while (visit->item_ != NODE_HEAD) {
      if (index == total) {
         // arrived at the node for specified index
         break;
      }

      visit = visit->next_;                                 // position cursor to child node
      total++;                                              // track traversal/visits
   }

   traverseCount_ += total;                                 // store traversals

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

// node initialization (see TIC )
void DListNode::initialize(int elem, DListNode *prev, DListNode *next) {
   item_ = elem;
   prev_ = prev;
   next_ = next;
}
