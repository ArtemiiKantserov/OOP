#ifndef SCAN_H
#define SCAN_H

#include "Ability.h"

class Scan : public Ability {
public:
  bool useAbility(int x, int y, GameField* field, bool& dual) override;
};

#endif