#include "interpret.hpp"
#include <fstream>
#include <iostream>

Command::Command(Type cmd_type) : type(cmd_type) {}
Command::Command(Type cmd_type, Direction direction)
    : type(cmd_type), move_direction(direction) {}

Interpret::Interpret(std::string filename) {
  std::ifstream file(filename);
  std::string line;
  while (std::getline(file, line)) {
    _script.push_back(line);
  }
  file.close();

  for (std::string &l : _script) {
    std::cout << l << std::endl;
  }
}
Command Interpret::next_command() {
  // todo interpret until comes to a command
  // then save state and return a command
}
