#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include "GameState.h"

#include <fstream>
#include <iostream>

class FileManager {
public:
  enum Target {READ, WRITE};
private:
  std::ifstream input_file_;
  std::ofstream output_file_;
public:
  FileManager(std::string file_name, Target target);
  ~FileManager();
  auto read_state(GameState& state) -> void;
  auto write_state(GameState state) -> void;
};

#endif 