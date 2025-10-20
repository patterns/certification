// SortedList.h; Hsin-ih Tu; 2025.10.16;
// Declaration of sorted circular double linked list

#ifndef SORTEDLIST_H
#define SORTEDLIST_H

#include <iostream>

const int NODE_HEAD = -99;         // the dummy item of the head node
const int NODE_UNDEFINED = -100;   // general node error (e.g., nonexistent)
const int ERROR_INDEX = -101;      // invalid index (parameter to retrieve)
const bool ADD_MODE_FRONT = true;  // add new nodes to front or tail

// nodes are linked together to make the list. The previous and next pointers
// are the reason the list is double linked.
template <typename T>
struct DListNode {
   T item_;
   DListNode *prev_;
   DListNode *next_;
   void initialize(T elem, DListNode *prev, DListNode *next);
   DListNode *clone(const int) const;
   DListNode *child() const;
   DListNode *parent() const;
};

//---------------------------------------------------------------------------
// SortedList:  circular double linked list composed of 'DListNode' nodes.
//
//
//
// Implementation and assumptions:
//   -- To
//   --
//   -- The add operation
//   -- The beginning of the list is marked by the 'header_' attribute.
//   -- header_ is a pointer to a dummy 'DListNode' with the tail node
//      linked by the previous pointer.
template <typename Object = int>
class SortedList {

public:
   SortedList();  // the constructor
   SortedList(const SortedList<Object>&);
   ~SortedList();  // the destructor
   int getCurrentSize() const;
   bool isEmpty() const;
   bool add(Object);
   bool remove(Object);
   void clear();
   virtual bool contains(Object);
   int getTraverseCount() const;
   ////Object retrieve(const int index);
   void resetTraverseCount();
   SortedList<Object>& operator=(const SortedList<Object>&);    // assignment copy
   int size() const;
   template <typename T>
   friend std::ostream& operator<<(std::ostream&, const SortedList<T>&);  // print stream
   Object operator[](const int);

private:
   DListNode<Object> *header_;
   int traverseCount_;
   int length_;
   DListNode<Object> *tailNode();
   DListNode<Object> *zeroNode() const;
   void deleteNode(DListNode<Object> *);
   int elementIndex(Object);
   void traversePlus(int);
   bool isHeadNode(DListNode<Object> *) const;
   bool elementMatch(DListNode<Object> *, Object) const;

};

#include "SortedList.cpp"
#endif
