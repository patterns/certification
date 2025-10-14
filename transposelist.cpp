// TransposeList.cpp; Hsin-ih Tu; 2025.10.13;
// Transpose list
//

#include "transposelist.h"

// node membership
bool TransposeList::contains(int elem) {
   int index = elementIndexTranspose(elem);
   if (index == NODE_UNDEFINED) {
      return false;
   }

   return true;
}

// the node index of the element specified will be x-1 in Transpose
// swap the accessed node with the previous one in this version.
int TransposeList::elementIndexTranspose(int elem) {
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
      total++;                 // track traversal/visits
      index++;
   }

   traversePlus(total);  // store traversals

   if (isHeadNode(visit)) {
      // we looped through whole list, but no match
      return NODE_UNDEFINED;
   }

   if (index == 0) {
      return 0;          // already at position 0, swap unecessary
   }


   // swap with x-1 position
   switch (length_) {
      case 0:  // unreachable
         break;

      case 1:  // single node
         break;

      case 2: {  // two nodes
         DListNode * n0 = zeroNode();
         DListNode * tn = tailNode();

         n0->next_ = header_;
         n0->prev_ = tn;
         tn->prev_ = header_;
         tn->next_ = n0;

         header_->next_ = tn;
         header_->prev_ = n0;
         break;
      }
      default: {

         if (index == (length_ -1)) { // at the tail
            DListNode *parent = visit->parent();
            DListNode *grand = parent->parent();

            parent->next_ = header_;
            grand->next_ = visit;
            visit->next_ = parent;

            parent->prev_ = visit;
            visit->prev_ = grand;
            header_->prev_ = parent;
         } else {  // general case
            DListNode *parent = visit->parent();
            DListNode *grand = parent->parent();
            DListNode *child = visit->child();

            parent->next_ = child;
            grand->next_ = visit;
            visit->next_ = parent;

            parent->prev_ = visit;
            visit->prev_ = grand;
            child->prev_ = parent;
         }
      }
   }
   return 0;
}
