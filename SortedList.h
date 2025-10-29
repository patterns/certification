// SortedList.h; Hsin-ih Tu; 2025.10.16;
// Declaration of sorted circular double linked list

#ifndef SORTEDLIST_H
#define SORTEDLIST_H

#include <iostream>
#include "SListNode.h"

const int NODE_UNDEFINED = -100;  // general node error (e.g., nonexistent)
const int ERROR_INDEX = -101;     // invalid index (parameter to retrieve)

//---------------------------------------------------------------------------
// SortedList:  circular double linked list composed of 'SListNode' nodes.
//   Each list node has the data stored as the item attribute.
//
// Implementation and assumptions:
//   -- Assumption is that duplicate items are allowed.
//   -- The beginning of the list is marked by the 'header_' attribute.
//   -- header_ is a pointer to a dummy 'SListNode' with the tail node
//      linked by the previous pointer.
template <typename Object>
class SortedList {
public:
   SortedList();  // the constructor
   SortedList(const SortedList<Object> &);     // copy-constructor
   SortedList(SortedList<Object> &&);    // move-constructor
   ~SortedList();  // the destructor
   int size() const;
   bool empty() const;
   bool insert(Object);
   bool remove(Object);
   void clear();
   SortedList<Object> &operator=(const SortedList<Object> &);  // assignment-copy
   SortedList<Object> &operator=(SortedList<Object> &&);       // assignment-move
   Object operator[](const int) const;                         // index access operator
   SortedList<Object> operator+(const SortedList<Object> &);   // append operator
   bool operator==(const SortedList<Object> &) const;         // equals operator
   template <typename T>
   friend std::ostream &operator<<(std::ostream &, const SortedList<T> &);  // print stream

private:
   SListNode<Object> *header;
   int length_;
   bool destroying_;
   SListNode<Object> *tailNode();
   SListNode<Object> *zeroNode() const;
   void deleteNode(SListNode<Object> *);
   int elementIndex(Object);

};

#include "SortedList.cpp"
#endif
