// CSS501:Program2; Hsin-ih Tu; 2025.10.28
// sorted list with string node item type

#include <iostream>
#include <string>

#include "SortedList.h"

using namespace std;

int main() {
   SortedList<std::string> lx;
   SortedList<std::string> ly;

   SortedList<std::string> l1;
   l1.insert("55");
   l1.insert("77");
   l1.insert("22");

   SortedList<std::string> l2(l1);    // copy ctor

   SortedList<std::string> l3;
   l3.insert("77");
   l3.insert("99");
   l3.insert("22");

   // call equals operator
   bool match = (l1 == l2);
   cout << "Expect lists (l1, l2) to be equal: " << match << endl;

   bool ident = (l2 == l2);
   cout << "Expect lists (l2, l2) to be identical: " << ident << endl;

   bool miss = (l1 == l3);
   cout << "Expect lists (l1, l3) to be unequal: " << miss << endl;

   bool empty = (lx == ly);
   cout << "Expect empty lists (lx, ly) to be equal: " << empty << endl;


   // append preparation
   SortedList<std::string> la1;
   la1.insert("44");
   la1.insert("88");
   la1.insert("22");

   SortedList<std::string> la2;
   la2.insert("5");
   la2.insert("9");
   la2.insert("3");

   // do merge
   SortedList<std::string> la3 = la1 + la2;

   cout << "Expect size to be 6: " << la3.size() << endl;
   cout << "Expect item 0 to be 22: " << la3[0] << endl;
   cout << "Expect item 1 to be 3: " << la3[1] << endl;
   cout << "Expect item 2 to be 44: " << la3[2] << endl;
   cout << "Expect item 3 to be 5: " << la3[3] << endl;
   cout << "Expect item 5 to be 9: " << la3[5] << endl;


   return 0;
}
