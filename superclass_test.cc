#include <gtest/gtest.h>

#include "CDLinkedList.h"

// Superclass behavior
TEST(SuperclassTest, empty_list) {
   CDLinkedList ls = CDLinkedList();

   // empty list
   EXPECT_EQ(ls.isEmpty(), true);
   EXPECT_EQ(ls.getCurrentSize(), 0);

   // count does not change
   EXPECT_EQ(ls.getTraverseCount(), 0);
   ls.add(55);
   EXPECT_EQ(ls.getTraverseCount(), 0);
}

TEST(SuperclassTest, node_creation) {
   CDLinkedList ls = CDLinkedList();
   bool added = ls.add(55);

   EXPECT_EQ(added, true);
   EXPECT_EQ(ls.isEmpty(), false);
   EXPECT_EQ(ls.getCurrentSize(), 1);
   EXPECT_EQ(ls.retrieve(0), 55);

   added = ls.add(77);

   EXPECT_EQ(added, true);
   EXPECT_EQ(ls.getCurrentSize(), 2);
   EXPECT_EQ(ls.retrieve(1), 77);
   EXPECT_EQ(ls.retrieve(100), ERROR_INDEX);

   added = ls.add(22);
   EXPECT_EQ(added, true);
   EXPECT_EQ(ls.getCurrentSize(), 3);
   EXPECT_EQ(ls.retrieve(2), 22);

   // no duplicates
   added = ls.add(77);
   EXPECT_EQ(added, false);
   // no negatives
   added = ls.add(-10);
   EXPECT_EQ(added, false);
}

TEST(SuperclassTest, list_reset) {
   CDLinkedList ls = CDLinkedList();
   bool added = ls.add(55);

   EXPECT_EQ(added, true);

   ls.clear();

   EXPECT_EQ(ls.isEmpty(), true);
}

TEST(SuperclassTest, node_deletion) {
   CDLinkedList ls = CDLinkedList();

   bool added = ls.add(55);

   EXPECT_EQ(added, true);
   EXPECT_EQ(ls.getCurrentSize(), 1);
   EXPECT_EQ(ls.isEmpty(), false);

   bool remed = ls.remove(55);
   EXPECT_EQ(remed, true);
   ////EXPECT_EQ(ls.getCurrentSize(), 0);
   EXPECT_EQ(ls.isEmpty(), true);
}


