#ifndef ABILITY_H
#define ABILITY_H

#include "GameField.h"

class Ability
{
public:
  virtual bool useAbility(int x, int y, GameField* field, bool& dual) = 0;
};

#endif
