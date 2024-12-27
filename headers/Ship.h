#ifndef SHIP_H
#define SHIP_H

#include <vector>
#include <string>
#include <iostream>

class Ship
{
public:
  // enum-класс состояния сегмента корабля
  enum Segment {
    FULL = 0,
    WOUNDED = 1,
    DESTROYED = 2
  };
  // инициализация из строки для загрузки игры из файла
  Ship(std::string str);
  // обычная инициализация
  Ship(int length);
  ~Ship()=default;
  auto get_length() -> int;
  auto is_destroyed() -> bool;
  auto get_status_segement(int segment_number) -> Segment;
  // bool отвечает разрушен ли корабль полностью или нет
  auto hit(int segment_number) -> bool;
  auto double_hit(int segment_number) -> bool;
  // провека на целостность всего
  auto full_destroyed() -> bool;
  auto serialize() -> std::string;
private:
  bool destroyed = false;
  int length_;
  std::vector<Segment> segment_status_;
};

#endif

