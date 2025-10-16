#include <gtest/gtest.h>

#include "transposelist.h"

// Transpose behavior
TEST(TransposeTest, empty_list) {
   TransposeList ls = TransposeList();

   // empty list
   EXPECT_EQ(ls.isEmpty(), true);
   EXPECT_EQ(ls.getCurrentSize(), 0);

   // count does not change
   EXPECT_EQ(ls.getTraverseCount(), 0);
   ls.add(55);
   EXPECT_EQ(ls.getTraverseCount(), 0);
}

TEST(TransposeTest, node_creation) {
   TransposeList ls = TransposeList();
   bool added = ls.add(55);

   EXPECT_EQ(added, true);
   EXPECT_EQ(ls.isEmpty(), false);
   EXPECT_EQ(ls.getCurrentSize(), 1);
   EXPECT_EQ(ls.retrieve(0), 55);

   added = ls.add(77);

   EXPECT_EQ(added, true);
   EXPECT_EQ(ls.getCurrentSize(), 2);
   EXPECT_EQ(ls.retrieve(0), 77);

   added = ls.add(22);
   EXPECT_EQ(added, true);
   EXPECT_EQ(ls.getCurrentSize(), 3);
   EXPECT_EQ(ls.retrieve(0), 22);

   // duplicates are ignored
   added = ls.add(77);
   EXPECT_EQ(added, true);
   EXPECT_EQ(ls.getCurrentSize(), 3);
   EXPECT_EQ(ls.retrieve(0), 77);

   // no negatives
   added = ls.add(-10);
   EXPECT_EQ(added, false);
   EXPECT_EQ(ls.retrieve(100), ERROR_INDEX);
}

TEST(TransposeTest, list_reset) {
   TransposeList ls = TransposeList();
   bool added = ls.add(55);

   EXPECT_EQ(added, true);

   ls.clear();

   EXPECT_EQ(ls.isEmpty(), true);
}

TEST(TransposeTest, node_deletion) {
   TransposeList ls = TransposeList();

   bool added = ls.add(55);

   EXPECT_EQ(added, true);
   EXPECT_EQ(ls.getCurrentSize(), 1);
   EXPECT_EQ(ls.isEmpty(), false);

   bool remed = ls.remove(55);
   EXPECT_EQ(remed, true);
   EXPECT_EQ(ls.isEmpty(), true);

   added = ls.add(55);
   added = ls.add(77);
   added = ls.add(88);
   added = ls.add(22);
   added = ls.add(11);

   EXPECT_EQ(added, true);
   EXPECT_EQ(ls.getCurrentSize(), 5);

   remed = ls.remove(88);
   EXPECT_EQ(remed, true);
   EXPECT_EQ(ls.getCurrentSize(), 4);
   EXPECT_EQ(ls.retrieve(1), 22);

   remed = ls.remove(11);
   EXPECT_EQ(remed, true);
   EXPECT_EQ(ls.getCurrentSize(), 3);
   EXPECT_EQ(ls.contains(11), false);
}

TEST(TransposeTest, node_membership) {
   TransposeList ls = TransposeList();
   bool added = ls.add(55);
   added = ls.add(77);
   added = ls.add(88);
   added = ls.add(22);
   added = ls.add(11);

   EXPECT_EQ(added, true);
   EXPECT_EQ(ls.getCurrentSize(), 5);

   bool match = ls.contains(55);

   EXPECT_EQ(match, true);

   match = ls.contains(88);

   EXPECT_EQ(match, true);
}

TEST(TransposeTest, node_creation_swap) {
   TransposeList ls = TransposeList();
   bool added = ls.add(55);
   added = ls.add(77);
   added = ls.add(88);
   added = ls.add(22);
   added = ls.add(11);

   EXPECT_EQ(added, true);
   EXPECT_EQ(ls.getCurrentSize(), 5);
   EXPECT_EQ(ls.retrieve(0), 11);

   added = ls.add(22);
   EXPECT_EQ(added, true);
   EXPECT_EQ(ls.getCurrentSize(), 5);
   EXPECT_EQ(ls.retrieve(0), 22);
   EXPECT_EQ(ls.retrieve(2), 88);
}

TEST(TransposeTest, node_membership_swap) {
   TransposeList ls = TransposeList();
   bool added = ls.add(55);
   added = ls.add(77);
   added = ls.add(88);
   added = ls.add(22);
   added = ls.add(11);

   EXPECT_EQ(added, true);
   EXPECT_EQ(ls.getCurrentSize(), 5);
   EXPECT_EQ(ls.retrieve(0), 11);

   bool match = ls.contains(22);
   EXPECT_EQ(match, true);
   EXPECT_EQ(ls.retrieve(0), 22);
   EXPECT_EQ(ls.retrieve(2), 88);
}

