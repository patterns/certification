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
   SortedList<int> testList;

   cout << "Make a list" << endl;

   testList.insert(1);
   testList.insert(7);
   testList.insert(8);
   testList.insert(5);
   testList.insert(1);


   cout << "#members 1->7->8->5->1: size=" << testList.size()
        << ", " << endl;
   ;

   dumpcopy<>(testList);

   cout << endl;
   testList.remove(8);

   cout << "#After remove 8, : size= " << testList.size()
        << ", " << endl;
   ;

   dumpcopy<>(testList);

   cout << endl;

   cout << "# members, after access 8: size= " << testList.size()
        << ", " << endl;
   ;

   dumpcopy<>(testList);


   cout << "# members, after access 7: size= " << testList.size()
        << ", " << endl;

   dumpcopy<>(testList);

   return 0;
}
