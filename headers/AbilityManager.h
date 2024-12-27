#ifndef ABILITY_MANAGER_H
#define ABILITY_MANAGER_H

#include "ShipManager.h"
#include "DoubleDamage.h"
#include "Scan.h"
#include "Shelling.h"
#include "Ability.h"

class AbilityManager
{
public:
  enum TypeAbility {
    DOUBLEDAMAGE = 0, 
    SCAN = 1,
    SHELLING = 2 
  };
  AbilityManager();
  AbilityManager(std::string str);
  ~AbilityManager();
  auto get_ability_name() -> std::string;
  auto get_ability_type() -> TypeAbility;
  auto ability() -> bool;
  auto add_ability(int n) -> void;
  auto add_abiliry_rand() -> void;
  auto use_ability(int x, int y, GameField* field, bool& dual) -> bool;
  auto serialize() -> std::string;
private:
  std::vector<TypeAbility> types_;
  std::vector<Ability*> array_ability_; 
};

#endif