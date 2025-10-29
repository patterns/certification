#include <gtest/gtest.h>
#include "SortedList.h"

// strings list TODO
TEST(SortedListTest, destructor_strings) {
   // std::string is not a builtin type
   SortedList<std::string> ls;    // item type: string

   ////ls.insert("x");
   ////EXPECT_EQ(ls.size(), 1);

   ////ls.clear();
   ////EXPECT_EQ(ls.size(), 0);

}

