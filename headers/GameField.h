#ifndef GAME_FIELD_H
#define GAME_FIELD_H

#include "Ship.h"
#include "Exceptions.h"

class GameField
{
public:
  // enum-класс состояния клетки поля для пользователя
  enum Status {
    UNKNOW = 0,
    SHIP = 1,
    SEA = 2
  };
  // структура хранящая в себе расположение кораблей для сохранения
  struct ShipPlacement {
    int index, x, y;
    bool orientation;
  };
  // структура содержащая всю информацию о определённой клетке
  struct CellCharacteristics {
    int segment_ship;
    Ship* ship;
    Status status;
  };
  GameField(std::string str);
  GameField(int width, int height);
  // конструктор копирования
  GameField(const GameField& other);
  // конструктор перемещения
  GameField(GameField&& other);
  // операторе присваивания
  GameField& operator=(const GameField& other);
  // оператор перемещения
  GameField& operator=(GameField&& other);
  ~GameField();
  auto add_ship(Ship* ship, int x, int y, bool orientation) -> void;
  auto add_ship_save(Ship* ship, int x, int y, bool orientation) -> void;
  auto attack(int x, int y, bool dual) -> bool;
  auto hidedn_attack(int x, int y, bool dual) ->bool;
  // метод устанавливающий статус UNKNOW во всех клетках
  auto fog_war() -> void;
  auto ship_segment(int x, int y) -> bool;
  auto serialize() -> std::string;
  auto get_width() -> int;
  auto get_height() -> int;
  auto get_cell(int x, int y) -> CellCharacteristics*;
private:
  int width_, height_;
  std::vector<std::vector<CellCharacteristics*>> field_;
};

#endif