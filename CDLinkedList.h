// CDLinkedList.h; Hsin-ih Tu; 2025.10.07;
// circular double linked list

#ifndef CDLINKEDLIST_H
#define CDLINKEDLIST_H

const int LIST_CAPACITY = (1024 - 1);
const int NODE_HEAD = -99;
const int NODE_UNDEFINED = -100;
const int ERROR_INDEX = -101;

// nodes are linked together to make the list. The previous and next pointers
// are the reason the list is double linked.
struct DListNode {
   int item_;
   DListNode *prev_;
   DListNode *next_;
   void initialize(int elem, DListNode *prev, DListNode *next);
};

//---------------------------------------------------------------------------
// CDLinkedList:  circular double linked list composed of 'DListNode' nodes.
//    In order to measure search performance, we track traversal totals.
//    Example list, 1->8->7->5.
//
// Implementation and assumptions:
//   -- To designate error conditions, we reserve negative numbers.
//   -- Which means the valid numerical range for node items are 0 to MAX_INTEGER.
//   -- The add operation ignores duplicates.
//   -- The beginning of the list is marked by the 'header_' attribute.
//   -- header_ is a pointer to a dummy 'DListNode' with the tail node
//      linked by the previous pointer.

class CDLinkedList {
public:
   CDLinkedList();  // the constructor
   CDLinkedList(const CDLinkedList &);
   ~CDLinkedList();  // the destructor
   int getCurrentSize() const;
   bool isEmpty() const;
   bool add(int newEntry);
   bool remove(int anEntry);
   void clear();
   virtual bool contains(int anEntry);
   int getTraverseCount() const;
   int retrieve(const int index);
   void resetTraverseCount();

protected:
   DListNode *header_;
   int traverseCount_;
   int length_;
   DListNode *tailNode();
   void deleteNode(DListNode *);
   int elementIndex(int);
};

#endif
