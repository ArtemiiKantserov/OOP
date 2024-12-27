#ifndef SHIP_MANAGER_H
#define SHIP_MANAGER_H

#include "Ship.h"
#include "GameField.h"
#include "Exceptions.h"

class ShipManager
{
private:
  int number_ships_;
  std::vector<Ship*> array_ships_;
public:
  ShipManager(int n, std::vector<int> sizes);
  ShipManager(std::string str);
  ~ShipManager();
  // добавление определённого корабля на поле
  auto add_ship(GameField* field, int x, int y, bool orientastion, int number_ship) -> void;
  auto add_ship_save(GameField* field, int x, int y, bool orientastion, int number_ship) -> void;
  // проверка есть ли ещё целые корабли
  auto end() -> bool;
  auto get_number_ships() -> int;
  auto get_sizes() -> std::vector<int>;
  auto serialize() -> std::string;
};

#endif