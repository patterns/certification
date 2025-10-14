// MtfList.cpp; Hsin-ih Tu; 2025.10.13;
// Move to Front list
//

#include "mtflist.h"


// node membership
bool MtfList::contains(int elem) {
   int index = elementIndexMtf(elem);
   if (index == NODE_UNDEFINED) {
      return false;
   }

   return true;
}

// the node index of the element specified will be 0 in MTF
// move the accessed node to the front in this version.
int MtfList::elementIndexMtf(int elem) {
   if (isEmpty() || elem < 0) {
      return NODE_UNDEFINED;
   }

   int total = 0;
   DListNode *visit = header_->next_;                       // position cursor to zero node

   while (visit->item_ != NODE_HEAD) {
      if (visit->item_ == elem) {
         break;                                             // found a matching element
      }
      visit = visit->next_;                                 // position cursor to child node
      total++;                                              // track traversal/visits

   }

   traverseCount_ += total;                                 // store traversals

   if (visit->item_ == NODE_HEAD) {
      // we looped through whole list, but no match
      return NODE_UNDEFINED;
   }

   // splice new zero node
   DListNode *newNode = new DListNode;
   newNode->item_ = visit->item_;
   deleteNode(visit);

   switch (length_) {
      case 0: {  // empty list
            header_->next_ = newNode;
            header_->prev_ = newNode;
            newNode->prev_ = header_;
            newNode->next_ = header_;
            break;
         }
      case 1: {  // single node
            DListNode *n0 = header_->next_;
            n0->prev_ = newNode;
            header_->next_ = newNode;
            newNode->next_ = n0;
            newNode->prev_ = header_;
            break;
         }

      default: {
            DListNode *n0 = header_->next_;
            n0->prev_ = newNode;
            header_->next_ = newNode;
            newNode->next_ = n0;
            newNode->prev_ = header_;
      }
   }
   return 0;
}

