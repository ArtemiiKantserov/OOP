#include "../headers/FileManager.h"

FileManager::FileManager(std::string file_name, Target target) {
  if (target == Target::READ) {
    input_file_.open(file_name);
    if (!input_file_.is_open()){
      //hui
    }
  } else {
    output_file_.open(file_name);
    if (!output_file_.is_open()){
      //hui
    }
  }
}


auto FileManager::read_state(GameState& state) -> void {
  input_file_ >> state;
}

auto FileManager::write_state(GameState state) -> void {
  output_file_ << state; 
}

FileManager::~FileManager() {
  input_file_.close();
  output_file_.close();
}