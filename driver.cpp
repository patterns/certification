// CSS501:Program3; Hsin-ih Tu; 2025.11.14
// print PS statements to make Koch curve

#include <iostream>
#include <string>

#include "Koch.h"

int main(int argc, char **argv) {
  // sanity check input args
  if (argc != 6) {
    std::cout << "ERROR: Missing arguments!" << std::endl;
    return COMMAND_INVALID;
  }

  // TODO collect args into a config class (that contains these input validation
  // rules)
  int level = std::stoi(argv[5]);
  if (level < 0 || level > LEVEL_MAX) {
    std::cout << "ERROR: Unexpected Level argument!" << std::endl;
    return COMMAND_INVALID;
  }
  int y2 = std::stoi(argv[4]);
  if (y2 < -PAGE_HEIGHT || y2 > PAGE_HEIGHT) {
    std::cout << "ERROR: Unexpected y2 argument!" << std::endl;
    return COMMAND_INVALID;
  }
  int x2 = std::stoi(argv[3]);
  if (x2 < -PAGE_WIDTH || x2 > PAGE_WIDTH) {
    std::cout << "ERROR: Unexpected x2 argument!" << std::endl;
    return COMMAND_INVALID;
  }
  int y1 = std::stoi(argv[2]);
  if (y1 < -PAGE_HEIGHT || y1 > PAGE_HEIGHT) {
    std::cout << "ERROR: Unexpected y1 argument!" << std::endl;
    return COMMAND_INVALID;
  }
  int x1 = std::stoi(argv[1]);
  if (x1 < -PAGE_WIDTH || x1 > PAGE_WIDTH) {
    std::cout << "ERROR: Unexpected x1 argument!" << std::endl;
    return COMMAND_INVALID;
  }

  int v1[] = {x1, y1};
  int v2[] = {x2, y2};
  Koch k = Koch(level, v1, v2);
  bool ok = k.postscript();

  if (!ok) {
    std::cout << "ERROR: Koch curve failed for arguments: " << argv
              << std::endl;
    return RECURSION_UNDEFINED;
  }

  // emit PS instructions to draw the lines
  std::cout << LINE_WIDTH << " setlinewidth" << std::endl;
  std::cout << "stroke" << std::endl;
  std::cout << "showpage" << std::endl;

  return 0;
}
