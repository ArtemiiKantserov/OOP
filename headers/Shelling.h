#ifndef SHELLING_H
#define SHELLING_H

#include "Ability.h"

class Shelling : public Ability {
public:
  bool useAbility(int x, int y, GameField* field, bool& dual) override;
};

#endif