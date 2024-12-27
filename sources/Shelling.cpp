#include "../headers/Shelling.h"

bool Shelling::useAbility(int x, int y, GameField* field, bool& dual) {
  srand(time(NULL));
  while (1) {
    x = std::rand() % (field->get_width() + 1);
    y = std::rand() % (field->get_height() + 1);
    std::cout << x;
    if (field->ship_segment(x, y)) {
      field->hidedn_attack(x, y, dual);
      dual = false;
      break;
    }
  }
  return false;
}