#include <gtest/gtest.h>

#include "SortedList.h"

// List of unsigned int
TEST(SortedListTest, uint_empty_list) {
   SortedList<unsigned int> ls;

   // empty list
   EXPECT_EQ(ls.empty(), true);
   EXPECT_EQ(ls.size(), 0);
}

TEST(SortedListTest, uint_node_creation) {
   SortedList<unsigned int> ls;

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
}

TEST(SortedListTest, uint_list_reset) {
   SortedList<unsigned int> ls;

   bool added = ls.insert(55);

   EXPECT_EQ(added, true);

   ls.clear();

   EXPECT_EQ(ls.empty(), true);
}

TEST(SortedListTest, uint_node_deletion) {
   SortedList<unsigned int> ls;
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

TEST(SortedListTest, uint_move_assignment) {
   SortedList<unsigned int> l1;
   l1.insert(55);
   l1.insert(77);
   l1.insert(22);
   EXPECT_EQ(l1.size(), 3);

   SortedList<unsigned int> l2;
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

TEST(SortedListTest, uint_copy_assignment) {
   SortedList<unsigned int> l1;
   l1.insert(55);
   l1.insert(77);
   l1.insert(22);
   EXPECT_EQ(l1.size(), 3);

   SortedList<unsigned int> l2;
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

TEST(SortedListTest, uint_move_constructor) {
   SortedList<unsigned int> l1;
   l1.insert(55);
   l1.insert(77);
   l1.insert(22);
   EXPECT_EQ(l1.size(), 3);

   // constructor forcing the move (l1 to l2)
   SortedList<unsigned int> l2(std::move(l1));

   EXPECT_EQ(l1.empty(), true);
   EXPECT_EQ(l1.size(), 0);
   EXPECT_EQ(l2.size(), 3);
   EXPECT_EQ(l2[0], 22);
   EXPECT_EQ(l2[1], 55);
   EXPECT_EQ(l2[2], 77);
}

TEST(SortedListTest, uint_copy_constructor) {
   SortedList<unsigned int> l1;
   l1.insert(55);
   l1.insert(77);
   l1.insert(22);
   EXPECT_EQ(l1.size(), 3);

   // constructor (l2 is copy of l1)
   SortedList<unsigned int> l2(l1);

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


