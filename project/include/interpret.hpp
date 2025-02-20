#ifndef interpret_hpp_
#define interpret_hpp_

#include "direction.hpp"
#include <string>
#include <vector>

class Command {
public:
  enum class Type { MOVE, TURN_LEFT, TURN_RIGHT, SHOOT };
  Type type;
  Direction move_direction;

  Command(Type cmd_type);
  Command(Type cmd_type, Direction direction);
};

class Interpret {
private:
  std::vector<std::string> _script;
  size_t _current_line;

public:
  Interpret(std::string filename);
  Command next_command();
};

#endif
