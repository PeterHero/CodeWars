#ifndef interpret_hpp_
#define interpret_hpp_

#include "direction.hpp"
#include <string>
#include <vector>

#define CMD_MOVE "move"
#define CMD_TURN "turn"
#define CMD_SHOOT "shoot"
#define CMD_STRING "cmd"
#define ROBOT_STRING "robot"

class Command {
public:
    enum class Type { MOVE,
        TURN_LEFT,
        TURN_RIGHT,
        SHOOT,
        INVALID };
    Type type;
    Direction move_direction;

    Command(Type cmd_type);
    Command(Type cmd_type, Direction direction);
    static Command create_move(const std::string& parameter);
    static Command create_turn(const std::string& parameter);
};

class Interpret {
private:
    std::vector<std::vector<std::string>> _script;
    std::vector<std::string> _script_unsplitted;
    size_t _current_line;

    bool line_is_command();
    Command get_command();
    void next_line();

public:
    Interpret(const std::string& filename);
    Command next_command();
};

inline void Interpret::next_line()
{
    _current_line = (_current_line + 1) % _script.size();
}

#endif
