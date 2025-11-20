// Koch.h; Hsin-ih Tu; 2025.11.14
// declaration of Koch curve routines

#ifndef KOCHCURVE_H
#define KOCHCURVE_H

const int RECURSION_NORMAL = 0;
const int RECURSION_UNDEFINED = -99;
const int COMMAND_INVALID = -100;
const int LEVEL_MAX = 13;          // ps2pdf at lv11 makes 13mb pdf
const float PAGE_HEIGHT = 72 * 11; // based on point as 1/72 of inch
const float PAGE_WIDTH = 72 * 8.5;
const float LINE_WIDTH = 0;
const float SCALE_THIRD = 1 / 3; // keep third as fixed constant

//---------------------------------------------------------------------------
// Koch: Koch curve generation by recursion.
//   .
//
// Implementation and assumptions:
//   -- Assumption input vectors v1/v2 are coordinates expressed as integers.
//   -- Internally we keep v1/v2 as floats because thirds makes fractions.

class Koch {
public:
  Koch(int, int[2], int[2]); // the constructor
  ~Koch();                   // the destructor
  bool postscript();
  bool postscript(int);

private:
  int level_;
  float v1_[2];
  float v2_[2];
  int recurve(int level, float v1[2], float v2[2]);
  float distance() const;


};
#endif
