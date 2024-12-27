#include "../headers/AbilityManager.h"

AbilityManager::AbilityManager() {
  srand(time(NULL));
  int n1 = rand() % 3, n2;
  add_ability(n1);
  while (1) {
    n2 = std::rand() % 3;
    if (n1 != n2) {
      add_ability(n2);
      break;
    }
  }
  add_ability(3 - n1 - n2);
}

AbilityManager::AbilityManager(std::string str) {
  for (auto i : str) add_ability(i-'0');
}

AbilityManager::~AbilityManager() {
  for (Ability* ability : array_ability_) {
    delete ability; 
  }
  array_ability_.clear(); 
}

auto AbilityManager::get_ability_name() -> std::string {
  if (array_ability_.empty()){
    return nullptr;
  }
  switch (types_[0]) {
  case TypeAbility::DOUBLEDAMAGE:
    return "Double Damage";
    break;
  case TypeAbility::SCAN:
    return "Scan";
    break;
  case TypeAbility::SHELLING:
    return "Shelling";
    break;
  }
  return nullptr;
}

auto AbilityManager::get_ability_type() -> TypeAbility {
  if (array_ability_.empty()) {
    
  }
  return types_[0];
}

auto AbilityManager::ability() -> bool {
  if (array_ability_.empty()) return false;
  return true;
}


auto AbilityManager::add_ability(int n) -> void {
  switch (n) {
  case 0:
    array_ability_.push_back(new DoubleDamage());
    types_.push_back(TypeAbility::DOUBLEDAMAGE);
    break;
  case 1:
    array_ability_.push_back(new Scan());
    types_.push_back(TypeAbility::SCAN);
    break;
  case 2:
    array_ability_.push_back(new Shelling());
    types_.push_back(TypeAbility::SHELLING);
    break;
  }
}

auto AbilityManager::add_abiliry_rand() -> void {
  srand(time(NULL));
  int n = rand() % 3;
  add_ability(n);
}

auto AbilityManager::use_ability(int x, int y, GameField* field, bool& dual) -> bool {
  if (array_ability_.empty()) {
    throw LackAbillity();
  }
  bool fl = array_ability_[0]->useAbility(x, y, field, dual);
  for (int i = 0; i < array_ability_.size() - 1; ++i) {
    types_[i] = types_[i + 1];
    array_ability_[i] = array_ability_[i + 1];
  }
  types_.pop_back();
  array_ability_.pop_back();
  return fl;
}

auto AbilityManager::serialize() -> std::string {
  std::string res;
  for (int i = 0; i < types_.size(); ++i) res += std::to_string(static_cast<int>(types_[i]));
  return res;
}