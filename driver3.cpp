#include <iostream>
#include <string>

#include "SortedList.h"

using namespace std;

int main() {
   SortedList<int> alist;
   SortedList<string> strlist;

   alist.insert(55);
   alist.insert(88);
   alist.insert(22);
   alist.insert(44);

   cout << alist << endl;

   SortedList<int> blist(alist);

   cout << blist[1] << endl;

   strlist.insert("k");
   strlist.insert("a");
   strlist.insert("x");
   strlist.insert("y");
   strlist.insert("z");

   // equals test
   SortedList<string> cplist(strlist);
   if (strlist == cplist) {
      cout << cplist << endl;
   }

   return 0;
}
