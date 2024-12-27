#include "../headers/GameState.h"


std::ostream& operator<<(std::ostream& out, const GameState& state) {
  out << state.user_ships_ << "\n"
      << state.user_placement_ << "\n"
      << state.user_field_ << "\n"
      << state.user_ability_ << "\n"
      << state.comp_ships_ << "\n"
      << state.comp_placement_ << "\n"
      << state.comp_field_ << "\n";
  return out;
}

std::istream& operator>>(std::istream& in, GameState& state) {
  std::string temp;
  getline(in, temp);
  state.set_ship_manager(temp, GameState::PlayerType::PLAYER);
  getline(in, temp);
  state.set_ship_placement(temp, GameState::PlayerType::PLAYER);
  getline(in, temp);
  state.set_game_field(temp, GameState::PlayerType::PLAYER);
  getline(in, temp);
  state.set_ability_manager(temp);
  getline(in, temp);
  state.set_ship_manager(temp, GameState::PlayerType::COMPUTER);
  getline(in, temp);
  state.set_ship_placement(temp, GameState::PlayerType::COMPUTER);
  getline(in, temp);
  state.set_game_field(temp, GameState::PlayerType::COMPUTER);
  return in;
}

auto GameState::set_ship_manager(std::string ships, PlayerType who) -> void {
  if (who == GameState::PlayerType::COMPUTER) {
    comp_ships_ = ships;
  } else {
    user_ships_ = ships;
  }
}

auto GameState::set_game_field(std::string field, PlayerType who) -> void {
  if (who == GameState::PlayerType::COMPUTER) {
    comp_field_ = field;
  } else {
    user_field_ = field;
  }
}

auto GameState::set_ability_manager(std::string ability) -> void {
  user_ability_ = ability;
}

auto GameState::set_ship_placement(std::string placement, PlayerType who) -> void {
  if (who == GameState::PlayerType::COMPUTER) {
    comp_placement_ = placement;
  } else {
    user_placement_ = placement;
  }
}

auto GameState::get_ship_manager(PlayerType who) -> std::string {
  if (who == GameState::PlayerType::COMPUTER) {
    return comp_ships_;
  }
  return user_ships_;
}

auto GameState::get_game_field(PlayerType who) -> std::string {
  if (who == GameState::PlayerType::COMPUTER) {
    return comp_field_;
  }
  return user_field_;
}

auto GameState::get_ability_manager() -> std::string {
  return user_ability_;  
}

auto GameState::get_ship_placement(PlayerType who) -> std::string {
  if (who == GameState::PlayerType::COMPUTER) {
    return comp_placement_;
  }
  return user_placement_;
}