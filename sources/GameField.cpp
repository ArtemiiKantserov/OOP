#include "../headers/GameField.h"
#include <iostream>
#include <string>

GameField::GameField(std::string str) {
  width_ = std::stoi(str.substr(0, str.find(" ")));
  str = str.substr(str.find(" ") + 1);
  height_ = std::stoi(str.substr(0, str.find(" ")));
  str = str.substr(str.find(" ") + 1);
  field_ = std::vector<std::vector<CellCharacteristics*>>(height_ + 2, std::vector<CellCharacteristics*>(width_ + 2, nullptr));
  for (int y = 0; y < height_ + 2; ++y) {
    for (int x = 0; x < width_ + 2; ++x) {
      field_[y][x] = new CellCharacteristics;
      field_[y][x]->ship = nullptr;
    }
  }
  for (int y = 1; y < height_ + 1; ++y) {
    for (int x = 1; x < width_ + 1; ++x) {
      field_[y][x]->status = Status::SEA;
    }
  }
  for (int y = 1; y < height_ + 1; ++y) {
    for (int x = 1; x < width_ + 1; ++x)
      field_[y][x]->status = Status(std::stoi(str.substr(x-1, 1)));
    str = str.substr(width_);
  }
}

GameField::GameField(int width, int height) {
  height_ = height;
  width_ = width;
  field_ = std::vector<std::vector<CellCharacteristics*>>(height_ + 2, std::vector<CellCharacteristics*>(width_ + 2, nullptr));
  for (int y = 0; y < height_ + 2; ++y) {
    for (int x = 0; x < width_ + 2; ++x) {
      field_[y][x] = new CellCharacteristics;
      field_[y][x]->ship = nullptr;
    }
  }
  for (int y = 1; y < height_ + 1; ++y) {
    for (int x = 1; x < width_ + 1; ++x) {
      field_[y][x]->status = Status::SEA;
    }
  }
}

GameField::GameField(const GameField& other): height_(other.height_), width_(other.width_), field_(std::vector<std::vector<CellCharacteristics*>>(other.height_, std::vector<CellCharacteristics*>(other.width_))){
  field_ = other.field_;
}

GameField& GameField::operator=(const GameField& other) {
  GameField temp(other);
  std::swap(height_, temp.height_);
  std::swap(width_, temp.width_);
  std::swap(field_, temp.field_);
  return *this;
}

GameField::GameField(GameField&& other) {
  std::swap(height_, other.height_);
  std::swap(width_, other.width_);
  std::swap(field_, other.field_);
}

GameField& GameField::operator=(GameField&& other) {
  if (this != &other) {
    std::swap(height_, other.height_);
    std::swap(width_, other.width_);
    std::swap(field_, other.field_);
  }
  return *this;
}

GameField::~GameField() {
  for (auto& row : field_) {
    for (auto* cell : row)
      delete cell;
  }
  field_.clear(); 
}

auto GameField::add_ship(Ship* ship, int x, int y, bool orientation) -> void {
  if (orientation) {
    for (int i = 0; i < ship->get_length(); ++i) {
      field_[y+i][x]->ship = ship;
      field_[y+i][x]->status = GameField::Status::SHIP;
      field_[y+i][x]->segment_ship = i;
    }
  } else {
    for (int i = 0; i < ship->get_length(); ++i) {
      field_[y][x+i]->ship = ship;
      field_[y][x+i]->status = GameField::Status::SHIP;
      field_[y][x+i]->segment_ship = i;
    }
  }
}

auto GameField::attack(int x, int y, bool dual) -> bool {
  if (field_[y][x]->ship == nullptr) {
    field_[y][x]->status = Status::SEA;
    return false;
  } else {
    field_[y][x]->status = Status::SHIP;
    if (!dual) return field_[y][x]->ship->hit(field_[y][x]->segment_ship);
    else return field_[y][x]->ship->double_hit(field_[y][x]->segment_ship);
  }
}

auto GameField::hidedn_attack(int x, int y, bool dual) ->bool {
  if (field_[y][x]->ship == nullptr) return false;
  else {
    if (!dual) return field_[y][x]->ship->hit(field_[y][x]->segment_ship);
    else return field_[y][x]->ship->double_hit(field_[y][x]->segment_ship);
  }
}

auto GameField::fog_war() -> void {
  for (int y = 1; y < height_ + 1; ++y) {
    for (int x = 1; x < width_ + 1; ++x) {
      field_[y][x]->status = Status::UNKNOW;
    }
  }
}

auto GameField::ship_segment(int x, int y) -> bool {
  if (field_[y][x]->ship != nullptr) return true;
  return false;
}

auto GameField::serialize() -> std::string {
  std::string res;
  res += std::to_string(width_);
  res += " ";
  res += std::to_string(height_);
  res += " ";
  for (int y = 1; y < height_ + 1; ++y) {
    for (int x = 1; x < width_ + 1; ++x)
      res += std::to_string(static_cast<int>(field_[y][x]->status));
  }
  return res;
}

auto GameField::get_width() -> int {
  return width_;
}

auto GameField::get_height() -> int {
  return height_;
}

auto GameField::get_cell(int x, int y) -> GameField::CellCharacteristics* {
  return field_[y][x];
}