#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "ShipManager.h"

#include <fstream>

class GameState
{
public:
  enum PlayerType {
    PLAYER = 0, 
    COMPUTER = 1
  };
  GameState()=default;
  ~GameState()=default;
  friend std::ostream& operator<<(std::ostream& out, const GameState& state);
  friend std::istream& operator>>(std::istream& in, GameState& state);
  auto set_ship_manager(std::string ships, PlayerType who) -> void;
  auto set_game_field(std::string field, PlayerType who) -> void;
  auto set_ability_manager(std::string ability) -> void;
  auto set_ship_placement(std::string placement, PlayerType who) -> void;
  auto get_ship_manager(PlayerType who) -> std::string;
  auto get_game_field(PlayerType who) -> std::string;
  auto get_ability_manager() -> std::string;
  auto get_ship_placement(PlayerType who) -> std::string;
private:
  std::string comp_field_, user_field_;
  std::string user_ships_, comp_ships_;
  std::string user_placement_, comp_placement_;
  std::string user_ability_;
};

#endif