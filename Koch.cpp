// Koch.cpp; Hsin-ih Tu; 2025.11.19
// definition of Koch curve members and methods

#include <cmath>
#include <iostream>
////#include <doctest/doctest.h>

#include "Koch.h"

// constructor
Koch::Koch(int level, int v1[2], int v2[2]) {
  level_ = level;
  v1_[0] = v1[0];
  v1_[1] = v1[1];
  v2_[0] = v2[0];
  v2_[1] = v2[1];
}

// deconstructor
Koch::~Koch() {}

// generate postscript statements
bool Koch::postscript() { return postscript(level_); }

// generate postscript with specified level
bool Koch::postscript(int level) {

  // handle level zero (because recursion will fall through to the zero case)
  if (level == 0) { // base case, draw line
    std::cout << v1_[0] << " " << v1_[1] << " moveto" << std::endl;
    std::cout << v2_[0] << " " << v2_[1] << " lineto" << std::endl;
    return true;
  }

  int status = recurve(level, v1_, v2_);
  return (status == RECURSION_NORMAL);
}

int Koch::recurve(int level, float v1[2], float v2[2]) {
  if (level == 0) { // done
    return RECURSION_NORMAL;
  }

  int total = distance();
  float third = total / 3;        // ???idea, can we precalculate
  float second = (total / 3) * 2; // ???idea, can we precalculate

  float xd = v2[0] - v1[0];
  float yd = v2[1] - v1[1];
  float u[] = {(xd / total), (yd / total)}; // unit vector
  ////float p1[] = resize(u, total, first);
  float p1[] = {v1[0] + (third * u[0]), v1[1] + (third * u[1])}; // vertex1
  ////float p2[] = resize(u, total, false);
  float p2[] = {v1[0] + (second * u[0]), v1[1] + (second * u[1])}; // vertex2
  // v3 = ( (x1 + x2 + Sqrt[3] (y1 - y2) )/2, (y1 + y2 + Sqrt[3] (x2 - x1) )/2)
  float xm = (p1[0] + p2[0] + sqrt(3) * (p1[1] - p2[1])) / 2;
  float ym = (p1[1] + p2[1] + sqrt(3) * (p2[0] - p1[0])) / 2;
  float p3[] = {xm, ym}; // vertex3

  if (level == 1) { // base case, bump
    std::cout << v1[0] << " " << v1[1] << " moveto" << std::endl;
    std::cout << p1[0] << " " << p1[1] << " lineto" << std::endl;
    std::cout << p3[0] << " " << p3[1] << " lineto" << std::endl;
    std::cout << p2[0] << " " << p2[1] << " lineto" << std::endl;
    std::cout << v2[0] << " " << v2[1] << " lineto" << std::endl;
    return RECURSION_NORMAL;
  }

  // TODO beyond lv 5, from lv 6 the recursion is making duplicate lines!
  //      ***suggestion about not allowing duplicate endpoints/vertices
  //      ???idea, is this similar to factorial (wasteful repeating calc)
  // level >1
  // recursion, for each pair of segment points call (level - 1)
  int status = RECURSION_UNDEFINED;
  int sublv = level - 1;
  status = recurve(sublv, v1, p1); // left segment
  if (status == RECURSION_NORMAL) {
    status = recurve(sublv, p1, p3); // triangle side A
    status = recurve(sublv, p3, p2); // triangle side B
    if (status == RECURSION_NORMAL) {
      status = recurve(sublv, p2, v2); // right segment
    }
  }

  return status;
}

float Koch::distance() const {
  float dx = v2_[0] - v1_[0];
  float dy = v2_[1] - v1_[1];
  double subtotal = std::pow(dx, 2) + std::pow(dy, 2);
  return std::sqrt(subtotal);
}
/*
// See https://www.oreilly.com/library/view/c-cookbook/0596007612/ch11s13.html
*/

/**************************************


TEST_CASE("testing the ") {
////    CHECK(factorial(0) == 1);
    // see fail
    CHECK(1 == 0);

}
************************************/
