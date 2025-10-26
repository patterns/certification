#include <iostream>
#include <string>

#include "SortedList.h"

using namespace std;

int main() {
   SortedList<int> alist;
   SortedList<string> strlist;

   alist.insert(3);
   alist.insert(1);

   cout << alist[0] << endl;

   SortedList<int> blist(alist);

   cout << blist[1] << endl;

   strlist.insert("k");
   strlist.insert("a");

   return 0;
}
