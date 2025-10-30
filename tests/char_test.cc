#include <gtest/gtest.h>

#include "SortedList.h"

TEST(SortedListTest, char_list_append) {
   // first list
   SortedList<char> l1;
   l1.insert(44);
   l1.insert(88);
   l1.insert(22);
   EXPECT_EQ(l1.size(), 3);

   // second list
   SortedList<char> l2;
   l2.insert(5);
   l2.insert(9);
   l2.insert(3);
   EXPECT_EQ(l2.size(), 3);

   // merge lists
   SortedList<char> l3 = l1 + l2;

   EXPECT_EQ(l3.size(), 6);
   EXPECT_EQ(l3[0], 3);
   EXPECT_EQ(l3[1], 5);
   EXPECT_EQ(l3[2], 9);
   EXPECT_EQ(l3[3], 22);
   EXPECT_EQ(l3[5], 88);

}

TEST(SortedListTest, char_list_equals) {
   SortedList<char> lx;
   SortedList<char> ly;

   SortedList<char> l1;
   l1.insert(55);
   l1.insert(77);
   l1.insert(22);

   SortedList<char> l2;
   l2.insert(55);
   l2.insert(77);
   l2.insert(22);

   SortedList<char> l3;
   l3.insert(77);
   l3.insert(99);
   l3.insert(22);

   // call equals operator
   bool match = (l1 == l2);
   EXPECT_EQ(match, true);

   bool ident = (l2 == l2);
   EXPECT_EQ(ident, true);

   bool miss = (l1 == l3);
   EXPECT_EQ(miss, false);

   bool empty = (lx == ly);
   EXPECT_EQ(empty, true);

}

// List behavior
TEST(SortedListTest, char_list_empty) {
   SortedList<char> ls;

   // empty list
   EXPECT_EQ(ls.empty(), true);
   EXPECT_EQ(ls.size(), 0);
}


TEST(SortedListTest, char_node_creation) {
   SortedList<char> ls;

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
   SortedList<char> l2;
   l2.insert(5);
   l2.insert(9);
   l2.insert(3);
   EXPECT_EQ(l2.size(), 3);
   EXPECT_EQ(l2[0], 3);
   EXPECT_EQ(l2[1], 5);
   EXPECT_EQ(l2[2], 9);
   // third list
   SortedList<char> l3;
   l3.insert(9);
   l3.insert(5);
   l3.insert(3);
   EXPECT_EQ(l3.size(), 3);
   EXPECT_EQ(l3[0], 3);
   EXPECT_EQ(l3[1], 5);
   EXPECT_EQ(l3[2], 9);
   // fourth list
   SortedList<char> l4;
   l4.insert(5);
   l4.insert(3);
   l4.insert(9);
   EXPECT_EQ(l4.size(), 3);
   EXPECT_EQ(l4[0], 3);
   EXPECT_EQ(l4[1], 5);
   EXPECT_EQ(l4[2], 9);

   SortedList<char> l5;
   l5.insert(3);
   l5.insert(9);
   EXPECT_EQ(l5.size(), 2);
   EXPECT_EQ(l5[0], 3);
   EXPECT_EQ(l5[1], 9);

   SortedList<char> l6;
   l6.insert(9);
   l6.insert(3);
   EXPECT_EQ(l6.size(), 2);
   EXPECT_EQ(l6[0], 3);
   EXPECT_EQ(l6[1], 9);
}

TEST(SortedListTest, char_list_reset) {
   SortedList<char> ls;

   bool added = ls.insert(55);

   EXPECT_EQ(added, true);

   ls.clear();

   EXPECT_EQ(ls.empty(), true);
}

TEST(SortedListTest, char_node_deletion) {
   SortedList<char> ls;
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

TEST(SortedListTest, char_move_assignment) {
   SortedList<char> l1;
   l1.insert(55);
   l1.insert(77);
   l1.insert(22);
   EXPECT_EQ(l1.size(), 3);

   SortedList<char> l2;
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

TEST(SortedListTest, char_copy_assignment) {
   SortedList<char> l1;
   l1.insert(55);
   l1.insert(77);
   l1.insert(22);
   EXPECT_EQ(l1.size(), 3);

   SortedList<char> l2;
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

TEST(SortedListTest, char_move_constructor) {
   SortedList<char> l1;
   l1.insert(55);
   l1.insert(77);
   l1.insert(22);
   EXPECT_EQ(l1.size(), 3);

   // constructor forcing the move (l1 to l2)
   SortedList<char> l2(std::move(l1));

   EXPECT_EQ(l1.empty(), true);
   EXPECT_EQ(l1.size(), 0);
   EXPECT_EQ(l2.size(), 3);
   EXPECT_EQ(l2[0], 22);
   EXPECT_EQ(l2[1], 55);
   EXPECT_EQ(l2[2], 77);
}

TEST(SortedListTest, char_copy_constructor) {
   SortedList<char> l1;
   l1.insert(55);
   l1.insert(77);
   l1.insert(22);
   EXPECT_EQ(l1.size(), 3);

   // constructor (l2 is copy of l1)
   SortedList<char> l2(l1);

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


