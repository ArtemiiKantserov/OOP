#ifndef GAME_H
#define GAME_H

#include "AbilityManager.h"
#include "GameState.h"
#include "FileManager.h"

#include <random>

class Game
{
public:
  enum Turn{
    ABILITY = 0, 
    ATTACK = 1
  };
  Game()=default;
  ~Game() = default;
  auto start_game(std::string file_name) -> void;
  auto start_game(int x, int y, int ship_num, std::vector<int> ship_sizes) -> void;
  auto add_ship_field(int x, int y, int index, bool orientation) -> void;
  auto comp_turn() -> bool;
  auto user_turn(Turn turn, int x, int y, bool& dual) -> bool;
  auto new_round() -> void;
  auto save_game(std::string file_name) -> void;
  auto load_game(std::string file_name) -> void;
  auto random_placement(bool who) -> void;
  auto get_field(bool who) -> GameField*;
  auto serialize(bool who) -> std::string;
  auto aserialize(std::string str, bool who) -> void;
private:
  GameField *comp_field_, *user_field_;
  ShipManager *comp_ships_, *user_ships_;
  AbilityManager *user_ability_;
  GameState state_;
  std::vector<GameField::ShipPlacement> comp_placement_, user_placement_;
};

#endif