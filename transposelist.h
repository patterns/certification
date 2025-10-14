// transposelist.h; Hsin-ih Tu; 2025.10.13;
// Transpose list

#include "CDLinkedList.h"

#ifndef TRANSPOSELIST_H
#define TRANSPOSELIST_H

//---------------------------------------------------------------------------
// TransposeList:  .
//
//
//
// Implementation and assumptions:
//   -- To

class TransposeList : public CDLinkedList {
public:
   virtual bool contains(int anEntry);

protected:
   int elementIndexTranspose(int);
};

#endif
