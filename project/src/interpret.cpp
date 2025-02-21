#include "interpret.hpp"
#include "plog/Log.h"
#include <fstream>
#include <sstream>

Command::Command(Type cmd_type) : type(cmd_type) {}
Command::Command(Type cmd_type, Direction direction)
    : type(cmd_type), move_direction(direction) {}

Command Command::create_move(const std::string &parameter) {
  if (parameter == DIRECTION_LEFT) {
    return Command(Type::MOVE, Direction::LEFT);
  } else if (parameter == DIRECTION_UP) {
    return Command(Type::MOVE, Direction ::UP);
  } else if (parameter == DIRECTION_RIGHT) {
    return Command(Type::MOVE, Direction ::RIGHT);
  } else if (parameter == DIRECTION_DOWN) {
    return Command(Type::MOVE, Direction ::DOWN);
  } else {
    return Command(Type::INVALID);
  }
}

Command Command::create_turn(const std::string &parameter) {
  if (parameter == DIRECTION_LEFT) {
    return Command(Type::TURN_LEFT);
  } else if (parameter == DIRECTION_RIGHT) {
    return Command(Type::TURN_RIGHT);
  } else {
    return Command(Type::INVALID);
  }
}

Interpret::Interpret(const std::string &filename) : _current_line(0) {
  std::ifstream file(filename);
  std::string line;
  while (std::getline(file, line)) {
    if (line != "") {
      _script_unsplitted.push_back(line);
      _script.push_back({});
      std::istringstream line_stream(line);
      std::string word;
      while (std::getline(line_stream, word, ' ')) {
        _script.back().push_back(word);
      }
    }
  }
  file.close();
}

bool Interpret::line_is_command() {
  std::vector<std::string> &line = _script[_current_line];
  return line.size() >= 3 && line[0] == ROBOT_STRING && line[1] == CMD_STRING;
}
Command Interpret::get_command() {
  std::vector<std::string> &line = _script[_current_line];

  PLOG_VERBOSE << _script_unsplitted[_current_line];

  std::string &cmd_string = line[2];

  if (cmd_string == CMD_SHOOT) {
    return Command(Command::Type::SHOOT);
  } else if (cmd_string == CMD_MOVE && line.size() == 4) {
    return Command::create_move(line[3]);
  } else if (cmd_string == CMD_TURN && line.size() == 4) {
    return Command::create_turn(line[3]);
  } else {
    return Command(Command::Type::INVALID);
  }
}

Command Interpret::next_command() {
  while (!line_is_command()) {
    // todo control flow
    next_line();
  }

  // todo check const references everywhere

  Command command = get_command();
  next_line();
  return command;
}
