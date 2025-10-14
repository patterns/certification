// mtflist.h; Hsin-ih Tu; 2025.10.13;
// Move to Front list

#include "CDLinkedList.h"

#ifndef MTFLIST_H
#define MTFLIST_H


//---------------------------------------------------------------------------
// MtfList:  .
//    
//    
//
// Implementation and assumptions:
//   -- To

class MtfList: public CDLinkedList {
public:
   virtual bool contains(int anEntry);
protected:
   int elementIndexMtf(int);
};

#endif
