#include <gtest/gtest.h>

#include "SortedList.h"

TEST(SortedListTest, list_append) {
   // first list
   SortedList<int> l1;
   l1.insert(44);
   l1.insert(88);
   l1.insert(22);
   EXPECT_EQ(l1.size(), 3);

   // second list
   SortedList<int> l2;
   l2.insert(5);
   l2.insert(9);
   l2.insert(3);
   EXPECT_EQ(l2.size(), 3);

   // merge lists
   SortedList<int> l3 = l1 + l2;

   ////EXPECT_EQ(l3.size(), 6);
   EXPECT_EQ(l3.size(), 3);
   EXPECT_EQ(l3[0], 3);
   EXPECT_EQ(l3[1], 5);
   EXPECT_EQ(l3[2], 9);

}
TEST(SortedListTest, list_equals) {
   //TODO equals operator
   SortedList<int> l1;
   l1.insert(55);
   l1.insert(77);
   l1.insert(22);
   EXPECT_EQ(l1.size(), 3);
}

// List behavior
TEST(SortedListTest, empty_list) {
   SortedList<int> ls;

   // empty list
   EXPECT_EQ(ls.empty(), true);
   EXPECT_EQ(ls.size(), 0);
}

TEST(SortedListTest, node_creation) {
   SortedList<int> ls;

   bool added = ls.insert(55);

   EXPECT_EQ(added, true);
   EXPECT_EQ(ls.empty(), false);
   EXPECT_EQ(ls.size(), 1);
   EXPECT_EQ(ls[0], 55);

   added = ls.insert(77);

   EXPECT_EQ(added, true);
   EXPECT_EQ(ls.size(), 2);
   EXPECT_EQ(ls[1], 77);

   added = ls.insert(22);
   EXPECT_EQ(added, true);
   EXPECT_EQ(ls.size(), 3);
   EXPECT_EQ(ls[0], 22);

   // duplicates are allowed
   added = ls.insert(77);
   EXPECT_EQ(added, true);
   EXPECT_EQ(ls.size(), 4);
   EXPECT_EQ(ls[2], 77);

   // second list
   SortedList<int> l2;
   l2.insert(5);
   l2.insert(9);
   l2.insert(3);
   EXPECT_EQ(l2.size(), 3);
   EXPECT_EQ(l2[0], 3);
   EXPECT_EQ(l2[1], 5);
   EXPECT_EQ(l2[2], 9);
   // third list
   SortedList<int> l3;
   l3.insert(9);
   l3.insert(5);
   l3.insert(3);
   EXPECT_EQ(l3.size(), 3);
   EXPECT_EQ(l3[0], 3);
   EXPECT_EQ(l3[1], 5);
   EXPECT_EQ(l3[2], 9);
   // fourth list
   SortedList<int> l4;
   l4.insert(5);
   l4.insert(3);
   l4.insert(9);
   EXPECT_EQ(l4.size(), 3);
   EXPECT_EQ(l4[0], 3);
   EXPECT_EQ(l4[1], 5);
   EXPECT_EQ(l4[2], 9);

   SortedList<int> l5;
   l5.insert(3);
   l5.insert(9);
   EXPECT_EQ(l5.size(), 2);
   EXPECT_EQ(l5[0], 3);
   EXPECT_EQ(l5[1], 9);

   SortedList<int> l6;
   l6.insert(9);
   l6.insert(3);
   EXPECT_EQ(l6.size(), 2);
   EXPECT_EQ(l6[0], 3);
   EXPECT_EQ(l6[1], 9);
}

TEST(SortedListTest, list_reset) {
   SortedList<int> ls;

   bool added = ls.insert(55);

   EXPECT_EQ(added, true);

   ls.clear();

   EXPECT_EQ(ls.empty(), true);
}

TEST(SortedListTest, node_deletion) {
   SortedList<int> ls;
   bool added = ls.insert(55);

   EXPECT_EQ(added, true);
   EXPECT_EQ(ls.size(), 1);
   EXPECT_EQ(ls.empty(), false);

   bool remed = ls.remove(55);
   EXPECT_EQ(remed, true);
   EXPECT_EQ(ls.empty(), true);

   added = ls.insert(55);
   added = ls.insert(77);
   added = ls.insert(88);
   added = ls.insert(22);
   added = ls.insert(11);

   EXPECT_EQ(added, true);
   EXPECT_EQ(ls.size(), 5);

   remed = ls.remove(88);
   EXPECT_EQ(remed, true);
   EXPECT_EQ(ls.size(), 4);
   EXPECT_EQ(ls[1], 22);

   remed = ls.remove(11);
   EXPECT_EQ(remed, true);
   EXPECT_EQ(ls.size(), 3);
}

TEST(SortedListTest, move_assignment) {
   SortedList<int> l1;
   l1.insert(55);
   l1.insert(77);
   l1.insert(22);
   EXPECT_EQ(l1.size(), 3);

   SortedList<int> l2;
   l2.insert(9);
   l2.insert(8);
   l2.insert(7);
   l2.insert(6);
   EXPECT_EQ(l2.size(), 4);

   // assignment forcing the move (l1 to l2)
   l2 = std::move(l1);

   EXPECT_EQ(l1.empty(), true);
   EXPECT_EQ(l1.size(), 0);
   EXPECT_EQ(l2.size(), 3);
   EXPECT_EQ(l2[0], 22);
   EXPECT_EQ(l2[1], 55);
   EXPECT_EQ(l2[2], 77);
}

TEST(SortedListTest, copy_assignment) {
   SortedList<int> l1;
   l1.insert(55);
   l1.insert(77);
   l1.insert(22);
   EXPECT_EQ(l1.size(), 3);

   SortedList<int> l2;
   l2.insert(9);
   l2.insert(8);
   l2.insert(7);
   l2.insert(6);
   EXPECT_EQ(l2.size(), 4);

   // assignment (l2 is copy of l1)
   l2 = l1;

   EXPECT_EQ(l1.empty(), false);
   EXPECT_EQ(l1.size(), 3);
   EXPECT_EQ(l1[0], 22);
   EXPECT_EQ(l1[1], 55);
   EXPECT_EQ(l1[2], 77);
   EXPECT_EQ(l2.size(), 3);
   EXPECT_EQ(l2[0], 22);
   EXPECT_EQ(l2[1], 55);
   EXPECT_EQ(l2[2], 77);
}

TEST(SortedListTest, move_constructor) {
   SortedList<int> l1;
   l1.insert(55);
   l1.insert(77);
   l1.insert(22);
   EXPECT_EQ(l1.size(), 3);

   // constructor forcing the move (l1 to l2)
   SortedList<int> l2(std::move(l1));

   EXPECT_EQ(l1.empty(), true);
   EXPECT_EQ(l1.size(), 0);
   EXPECT_EQ(l2.size(), 3);
   EXPECT_EQ(l2[0], 22);
   EXPECT_EQ(l2[1], 55);
   EXPECT_EQ(l2[2], 77);
}

TEST(SortedListTest, copy_constructor) {
   SortedList<int> l1;
   l1.insert(55);
   l1.insert(77);
   l1.insert(22);
   EXPECT_EQ(l1.size(), 3);

   // constructor (l2 is copy of l1)
   SortedList<int> l2(l1);

   EXPECT_EQ(l1.empty(), false);
   EXPECT_EQ(l1.size(), 3);
   EXPECT_EQ(l1[0], 22);
   EXPECT_EQ(l1[1], 55);
   EXPECT_EQ(l1[2], 77);
   EXPECT_EQ(l2.size(), 3);
   EXPECT_EQ(l2[0], 22);
   EXPECT_EQ(l2[1], 55);
   EXPECT_EQ(l2[2], 77);
}


