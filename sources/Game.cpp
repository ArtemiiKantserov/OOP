#include "../headers/Game.h"

// ~Game() {

// }

auto Game::start_game(std::string file_name) -> void {
  load_game(file_name);
}

auto Game::start_game(int x, int y, int ship_num, std::vector<int> ship_sizes) -> void {
  comp_field_ = new GameField(x, y);
  user_field_ = new GameField(x, y);
  user_ability_ = new AbilityManager();
  user_ships_ = new ShipManager(ship_num, ship_sizes);
  comp_ships_ = new ShipManager(ship_num, ship_sizes);
  try {
  random_placement(false);
  } catch (const char* e) {
    throw e;
  }
  comp_field_->fog_war();
}

auto Game::add_ship_field(int x, int y, int index, bool orientation) -> void {
  GameField::ShipPlacement placement;
  placement.index = index;
  placement.x = x;
  placement.y = y;
  placement.orientation = orientation;
  try{
    user_ships_->add_ship(user_field_, x, y, orientation, index);
  } catch (IncorrectPlaceShip& e) {
    throw e;
  }
  user_placement_.push_back(placement);
}

auto Game::comp_turn() -> bool {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> coordX(1, comp_field_->get_width());
  std::uniform_int_distribution<> coordY(1, comp_field_->get_height());
  int x = 0, y = 0;
  x = coordX(gen);
  y = coordY(gen);
  user_field_->attack(x, y, 0);
  return user_ships_->end();
}

auto Game::user_turn(Turn turn, int x, int y, bool& dual) -> bool{\
  if (x > comp_field_->get_width() || x <= 0 || y <= 0 || y > comp_field_->get_height()) {
    throw WrongCoordinates();
  }
  if (turn == Turn::ATTACK) {
    if (comp_field_->attack(x, y, dual)) {
      user_ability_->add_abiliry_rand();
    }
    dual = false;
  } else {
    try {
    if (user_ability_->use_ability(x, y, comp_field_, dual)) {
      user_ability_->add_abiliry_rand();
    }
    } catch (LackAbillity& e) {
      throw e;
    }
  }
  return comp_ships_->end();
}

auto Game::new_round() -> void {
  delete comp_field_;
  delete comp_ships_;
  comp_field_ = new GameField(user_field_->get_width(), user_field_->get_height());
  comp_ships_ = new ShipManager(user_ships_->get_number_ships(), user_ships_->get_sizes());
  comp_placement_.clear();
  try{
  random_placement(false);
  } catch (const char* e) {
    throw e;
  }
  comp_field_->fog_war();
}

auto Game::save_game(std::string file_name) -> void {
  FileManager file(file_name, FileManager::Target::WRITE);
  state_.set_ability_manager(user_ability_->serialize());
  state_.set_game_field(user_field_->serialize(), GameState::PlayerType::PLAYER);
  state_.set_game_field(comp_field_->serialize(), GameState::PlayerType::COMPUTER);
  state_.set_ship_manager(user_ships_->serialize(), GameState::PlayerType::PLAYER);
  state_.set_ship_manager(comp_ships_->serialize(), GameState::PlayerType::COMPUTER);
  state_.set_ship_placement(serialize(false), GameState::PlayerType::COMPUTER);
  state_.set_ship_placement(serialize(true), GameState::PlayerType::PLAYER);
  file.write_state(state_);
}

auto Game::load_game(std::string file_name) -> void {
  try {
  FileManager file(file_name, FileManager::Target::READ);
  file.read_state(state_);
  comp_field_ = new GameField(state_.get_game_field(GameState::PlayerType::COMPUTER));
  user_field_ = new GameField(state_.get_game_field(GameState::PlayerType::PLAYER));
  user_ability_ = new AbilityManager(state_.get_ability_manager());
  user_ships_ = new ShipManager(state_.get_ship_manager(GameState::PlayerType::PLAYER));
  comp_ships_ = new ShipManager(state_.get_ship_manager(GameState::PlayerType::COMPUTER));
  aserialize(state_.get_ship_placement(GameState::PlayerType::PLAYER), true);
  aserialize(state_.get_ship_placement(GameState::PlayerType::COMPUTER), false);
  for (int i = 0; i < comp_ships_->get_number_ships() ; ++i) {
    comp_ships_->add_ship_save(comp_field_, comp_placement_[i].x, comp_placement_[i].y, comp_placement_[i].orientation, comp_placement_[i].index);
    add_ship_field(user_placement_[i].x, user_placement_[i].y, user_placement_[i].index, user_placement_[i].orientation);
  }
  } catch (...) {
    throw "file is bad.";
  }
}

auto Game::random_placement(bool who) -> void {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> coordX(1, comp_field_->get_width());
  std::uniform_int_distribution<> coordY(1, comp_field_->get_height());
  int x = 0, y = 0;
  bool orientation;
  GameField::ShipPlacement placement;
  if (!who) {
    int count = comp_field_->get_width() * comp_field_->get_height() * 4, in = 0;
    for (int i = 0; i < comp_ships_->get_number_ships(); ++i) {
      placement.index = i;
      x = coordX(gen);
      y = coordY(gen);
      orientation = coordX(gen) % 2 ? true : false;
      try {
        comp_ships_->add_ship(comp_field_, x, y, orientation, i);
        placement.x = x;
        placement.y = y;
        placement.orientation = orientation;
      } catch (IncorrectPlaceShip& e){
        ++in;
        if (in == count) {
          throw "computer cry.";
        }
        --i;
        continue;
      }
      comp_placement_.push_back(placement);
    }
  }
}

auto Game::get_field(bool who) -> GameField* {
  if (!who) return comp_field_;
  return user_field_;
}

auto Game::serialize(bool who) -> std::string {
  std::string res;
  if (who) {
    for (int i = 0; i < user_ships_->get_number_ships(); ++i) {
      res += std::to_string(user_placement_[i].index);
      res += " ";
      res += std::to_string(user_placement_[i].orientation);
      res += " ";
      res += std::to_string(user_placement_[i].x);
      res += " ";
      res += std::to_string(user_placement_[i].y);
      res += " ";
    }
  } else {
    for (int i = 0; i < comp_ships_->get_number_ships(); ++i) {
      res += std::to_string(comp_placement_[i].index);
      res += " ";
      res += std::to_string(comp_placement_[i].orientation);
      res += " ";
      res += std::to_string(comp_placement_[i].x);
      res += " ";
      res += std::to_string(comp_placement_[i].y);
      res += " ";
    }
  }
  return res;
}

auto  Game::aserialize(std::string str, bool who) -> void {
  GameField::ShipPlacement placement;
  if (!who) {
    for (int i = 0; i < comp_ships_->get_number_ships(); ++i) {
      placement.index = std::stoi(str.substr(0, str.find(" ")));
      str = str.substr(str.find(" ") + 1);
      placement.orientation = std::stoi(str.substr(0, str.find(" ")));
      str = str.substr(str.find(" ") + 1);
      placement.x = std::stoi(str.substr(0, str.find(" ")));
      str = str.substr(str.find(" ") + 1);
      placement.y = std::stoi(str.substr(0, str.find(" ")));
      str = str.substr(str.find(" ") + 1);
      comp_placement_.push_back(placement);
    }
  } else {
    for (int i = 0; i < user_ships_->get_number_ships(); ++i) {
      placement.index = std::stoi(str.substr(0, str.find(" ")));
      str = str.substr(str.find(" ") + 1);
      placement.orientation = std::stoi(str.substr(0, str.find(" ")));
      str = str.substr(str.find(" ") + 1);
      placement.x = std::stoi(str.substr(0, str.find(" ")));
      str = str.substr(str.find(" ") + 1);
      placement.y = std::stoi(str.substr(0, str.find(" ")));
      str = str.substr(str.find(" ") + 1);
      user_placement_.push_back(placement);
    }
  }
}