#include <gtest/gtest.h>

#include "SortedList.h"

// Superclass behavior
TEST(SuperclassTest, empty_list) {
   SortedList<int> ls;

   // empty list
   EXPECT_EQ(ls.empty(), true);
   EXPECT_EQ(ls.size(), 0);
}

TEST(SuperclassTest, node_creation) {
   SortedList<int> ls;

   bool added = ls.insert(55);

   EXPECT_EQ(added, true);
   EXPECT_EQ(ls.empty(), false);
   EXPECT_EQ(ls.size(), 1);
   EXPECT_EQ(ls[0], 55);

   added = ls.insert(77);

   EXPECT_EQ(added, true);
   EXPECT_EQ(ls.size(), 2);
   EXPECT_EQ(ls[0], 77);

   added = ls.insert(22);
   EXPECT_EQ(added, true);
   EXPECT_EQ(ls.size(), 3);
   EXPECT_EQ(ls[0], 22);

   // duplicates are ignored
   added = ls.insert(77);
   EXPECT_EQ(added, true);
   EXPECT_EQ(ls.size(), 3);
   EXPECT_EQ(ls[0], 22);

   // no negatives
   added = ls.insert(-10);
   EXPECT_EQ(added, false);
   ////EXPECT_EQ(ls[100], ERROR_INDEX);
   EXPECT_EQ(ls[100], NULL);
}

TEST(SuperclassTest, list_reset) {
   SortedList<int> ls;

   bool added = ls.insert(55);

   EXPECT_EQ(added, true);

   ls.clear();

   EXPECT_EQ(ls.empty(), true);
}

TEST(SuperclassTest, node_deletion) {
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
   EXPECT_EQ(ls.contains(11), false);
}

TEST(SuperclassTest, node_membership) {
   SortedList<int> ls;

   bool added = ls.insert(55);
   added = ls.insert(77);
   added = ls.insert(88);
   added = ls.insert(22);
   added = ls.insert(11);

   EXPECT_EQ(added, true);
   EXPECT_EQ(ls.size(), 5);

   bool match = ls.contains(55);

   EXPECT_EQ(match, true);

   match = ls.contains(88);

   EXPECT_EQ(match, true);
}


