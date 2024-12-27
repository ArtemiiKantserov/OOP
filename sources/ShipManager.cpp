#include "../headers/ShipManager.h"

ShipManager::ShipManager(int n, std::vector<int> sizes) {
  number_ships_ = n;
  for (int i = 0; i < number_ships_; ++i) 
    array_ships_.push_back(new Ship(sizes[i]));
}

ShipManager::ShipManager(std::string str) {
  number_ships_ = std::stoi(str.substr(0, str.find(" ")));
  str = str.substr(str.find(" ") + 1);
  for (int i = 0; i < number_ships_; ++i) {
    array_ships_.push_back(new Ship(str.substr(0, str.find("&"))));
    str = str.substr(str.find("&") + 1);
  }
}

ShipManager::~ShipManager() {
  for (Ship* ship : array_ships_) {
    delete ship;
  }
  array_ships_.clear();
}

auto ShipManager::add_ship(GameField* field, int x, int y, bool orientastion, int number_ship) -> void {
  try {
  field->add_ship(array_ships_[number_ship], x, y, orientastion);
  } catch (IncorrectPlaceShip& e) {
    throw e;
  }
}

auto ShipManager::add_ship_save(GameField* field, int x, int y, bool orientastion, int number_ship) -> void {
  try {
  field->add_ship_save(array_ships_[number_ship], x, y, orientastion);
  } catch (IncorrectPlaceShip& e) {
    throw e;
  }
}

auto ShipManager::end() -> bool {
  for (Ship* ship : array_ships_) 
    if (!ship->is_destroyed()) return false;
  return true;
}

auto ShipManager::get_number_ships() -> int{
  return number_ships_;
}

auto ShipManager::get_sizes() -> std::vector<int> {
  std::vector<int> sizes(number_ships_);
  for (int i = 0; i < number_ships_; ++i)
    sizes[i] = array_ships_[i]->get_length();
  return sizes;
}

auto ShipManager::serialize() -> std::string {
  std::string res;
  res += std::to_string(number_ships_);
  res += " ";
  for (int i = 0; i < number_ships_; ++i)
    res += array_ships_[i]->serialize();
  return res;
}