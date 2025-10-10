// CDLinkedList.h; Hsin-ih Tu; 2025.10.07;
// circular double linked list

#ifndef CDLINKEDLIST_H
#define CDLINKEDLIST_H

////#include <string>

const int LIST_CAPACITY = (1024 - 1);
const int NODE_HEAD = -99;
const int NODE_UNDEFINED = -100;
const int ERROR_INDEX = -101;

// A node that will have two pointers, prev, and next
struct DListNode {  // a list node
   int item;
   DListNode *prev;
   DListNode *next;
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
   int traverseCount_ = 0;
};

#endif
