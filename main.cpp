#include "./headers/Game.h"
#include <iostream>

void rendering(Game* game) {
  GameField* c = game->get_field(0);
  GameField* u = game->get_field(1);
  int h = c->get_height();
  int w = c->get_width();
  GameField::CellCharacteristics* cell; 
  std::cout << "  ";
  for (int i = 1; i < w + 1; ++i) {
    std::cout << i << ' ';
  }
  std::cout << "    ";
  for (int i = 1; i < w + 1; ++i) {
    std::cout << i << ' ';
  }
  std::cout << std::endl;
  for (int y = 1; y < h + 1; ++y) {
    std::cout << y << ' ';
    for (int x = 1; x < w + 1; ++x) {
      cell = c->get_cell(x, y);
      switch (cell->status) {
      case GameField::Status::SEA:
        std::cout << "~ ";
        break;
      case GameField::Status::UNKNOW:
        std::cout << "0 ";
        break;
      case GameField::Status::SHIP:
        switch (cell->ship->get_status_segement(cell->segment_ship)) {
        case Ship::Segment::WOUNDED:
          std::cout << "s ";
          break;
        case Ship::Segment::DESTROYED:
          std::cout << "x ";
          break;
        case Ship::Segment::FULL:
          std::cout << "@ ";
        }
        break;
      }
    }
    std::cout << "    ";
    for (int x = 1; x < w + 1; ++x) {
      cell = u->get_cell(x, y);
      switch (cell->status) {
      case GameField::Status::SEA:
        std::cout << "~ ";
        break;
      case GameField::Status::UNKNOW:
        std::cout << "o ";
        break;
      case GameField::Status::SHIP:
        switch (cell->ship->get_status_segement(cell->segment_ship)) {
        case Ship::Segment::WOUNDED:
          std::cout << "s ";
          break;
        case Ship::Segment::DESTROYED:
          std::cout << "x ";
          break;
        case Ship::Segment::FULL:
          std::cout << "@ ";
        break;
        }
      }
    }
    std::cout << std::endl;
  }
}


int main () {
  bool fl = false;
  while(1) {
    Game *game = new Game();
    std::cout << "load?" << std::endl;
    int ab = 0;
    std::cin >> ab;
    int x = 0, y = 0;
    if (ab) {
      game->start_game("game.txt");
    } else {
      int count_ship = 0, size = 0;
      std::vector<int> sizes;
      std::cout << "x y" << std::endl;
      std::cin >> x >> y;
      std::cout << "count of ships: ";
      std::cin >> count_ship;
      for (int i = 0; i < count_ship; ++i) {
        std::cout << i+1 << " ship have size: ";
        std::cin >> size;
        sizes.push_back(size);
      }
      game->start_game(x, y, count_ship, sizes);
      int xs = 0, yx = 0, o = 0;
      bool orientation;
      for (int i = 0; i < count_ship; ++i) {
        std::cout << "x y o" << std::endl;
        std::cin >> x >> y >> o;
        if (o) {
          orientation = true;
        } else {
          orientation = false;
        }
        game->add_ship_field(x, y, i, orientation);
      }
    }
    // std::system("cls");
    rendering(game);
    bool dual = false;
    while (true) {
      if (game->comp_turn()) {
        // std::system("cls");
        rendering(game);
        std::cout << "lose" << std::endl;
        std::cout << "new game?" << std::endl;
        std::cin >> ab;
        if (!ab) {
          fl = true;
        }
        break;
      }
      std::cout << "save?" << std::endl;
      std::cin >> ab;
      if (ab) {
        game->save_game("game.txt");
      }
      std::cout << "ability?" << std::endl;
      std::cin >> ab;
      if (ab) {
        std::cout << "x y" << std::endl;
        std::cin >> x >> y;
        if (game->user_turn(Game::Turn::ABILITY, x, y, dual)) {
          // std::system("cls");
          rendering(game);
          std::cout << "win" << std::endl;
          std::cout << "new round?" << std::endl;
          std::cin >> ab;
          if (ab) {
            game->new_round();
          } else {
            fl = true;
          }
        }
      }
      // std::system("cls");
      rendering(game);
      std::cout << "atack\nx y" << std::endl;
      std::cin >> x >> y;
      if (game->user_turn(Game::Turn::ATTACK, x, y, dual)) {
        // std::system("cls");
        rendering(game);
        std::cout << "win" << std::endl;
        std::cout << "new round?" << std::endl;
        std::cin >> ab;
        if (ab) {
          game->new_round();
        } else {
          fl = true;
        }
      }
      // std::system("cls");
      rendering(game);
    }
    if (fl) {
      break;
    }
  }
}