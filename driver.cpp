// driver.cpp; Hsin-ih Tu; 2025.10.18
// main program to exercise sorted list implementation

#include <iostream>
#include <string>

#include "SortedList.h"

using namespace std;

template <typename T>
void dumpcopy(SortedList<T> sl) {
   // print copy
   cout << "dumping sorted list: " << sl << endl;
}

int main() {
   SortedList<> testList;

   // Reset all traverse count first
   testList.resetTraverseCount();
   cout << "Make a list" << endl;

   testList.add(1);
   testList.add(7);
   testList.add(8);
   testList.add(5);
   testList.add(1);

   cout << "Reset traverse count: traverseCount=" << testList.getTraverseCount() << endl;

   cout << "#members 1->7->8->5->1: size=" << testList.size()
        << ", traverseCount=" << testList.getTraverseCount() << endl;
   ;
   cout << "traverse count=" << testList.getTraverseCount() << endl;

   dumpcopy<>(testList);

   cout << endl;
   testList.remove(8);

   cout << "#After remove 8, : size= " << testList.size()
        << ", traverseCount=" << testList.getTraverseCount() << endl;
   ;
   cout << "traverse count=" << testList.getTraverseCount() << endl;

   dumpcopy<>(testList);

   cout << endl;
   cout << "testList.contains(8)=" << testList.contains(8) << endl;

   cout << "# members, after access 8: size= " << testList.size()
        << ", traverseCount=" << testList.getTraverseCount() << endl;
   ;

   dumpcopy<>(testList);

   cout << "testList.contains(7)=" << testList.contains(7) << endl;

   cout << "# members, after access 7: size= " << testList.size()
        << ", traverseCount=" << testList.getTraverseCount() << endl;

   dumpcopy<>(testList);

   return 0;
}
