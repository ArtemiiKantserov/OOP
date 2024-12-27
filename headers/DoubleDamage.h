#ifndef DOUBLE_DAMAGE_H
#define DOUBLE_DAMAGE_H

#include "Ability.h"

class DoubleDamage : public Ability {
public:
  bool useAbility(int x, int y, GameField* field, bool& dual) override;
};

#endif