// CDLinkedList.h; Hsin-ih Tu; 2025.10.07;
// circular double linked list

#ifndef CDLINKEDLIST_H
#define CDLINKEDLIST_H

////#include <string>

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
// CDLinkedList:  the
//    the .
//
// Implementation and assumptions:
//   -- with

class CDLinkedList {
public:
   CDLinkedList();  // the constructor
   CDLinkedList(const CDLinkedList &rhs);
   ~CDLinkedList();  // the destructor
   int getCurrentSize() const;
   bool isEmpty() const;
   bool add(int newEntry);
   bool remove(int anEntry);
   void clear();

   virtual bool contains(int anEntry);
   int getTraverseCount() const;
   int retrieve(const int index) const;
   void resetTraverseCount();

protected:
   DListNode *header_;  // a dummy header
   int traverseCount_;
   int length_;
   DListNode *indexToPointer_[LIST_CAPACITY];
};

#endif
