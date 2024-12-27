#include "../headers/Scan.h"

bool Scan::useAbility(int x, int y, GameField* field, bool& dual) {
  bool fl = false;
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      if (field->ship_segment(x + i, y + j)) {
        fl = true;
      }
    }
  }
  if (fl) std::cout << "Ship" << std::endl;
  else std::cout << "empty" << std::endl;
  std::cin.ignore();
  std::cin.get();
  return false;
}