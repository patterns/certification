#include <gtest/gtest.h>
#include <string>
#include "SortedList.h"

// index access behavior
TEST(SortedListTest, out_of_bounds) {

   SortedList<int> ls;    // item type: int

   // empty
   EXPECT_EQ(ls.empty(), true);
   EXPECT_EQ(ls.size(), 0);
   EXPECT_EQ(ls[0], int(NULL));

   // single node
   ls.add(55);
   EXPECT_EQ(ls.size(), 1);
   EXPECT_EQ(ls[11], int(NULL));
   EXPECT_EQ(ls[-99], int(NULL));

   SortedList<char> l2;    // item type: char

   // empty
   EXPECT_EQ(l2.empty(), true);
   EXPECT_EQ(l2.size(), 0);
   EXPECT_EQ(l2[-99], char(NULL));
}

TEST(SortedListTest, out_of_bounds_strings) {
   // std::string is not a builtin type and cannot be coerced to NULL

   SortedList<std::string> l3;    // item type: string

   // empty
   EXPECT_EQ(l3.empty(), true);
   EXPECT_EQ(l3.size(), 0);

   // instead of NULL we look for the default value of the type
   EXPECT_EQ(l3[-99], "");
}

