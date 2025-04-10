#ifndef interpret_hpp_
#define interpret_hpp_

#include "battle_helper.hpp"
#include "direction.hpp"
#include <string>
#include <vector>

using robot_id_t = size_t;
class Robot;

#define CMD_MOVE "move"
#define CMD_TURN "turn"
#define CMD_SHOOT "shoot"
#define CMD_STRING "cmd"
#define ROBOT_STRING "robot"
#define SEES_ENEMY "sees_enemy"

#define IF_STRING "if"
#define ELSE_STRING "else"
#define ENDIF_STRING "endif"

#define TRUE_STRING "true"
#define FALSE_STRING "false"

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
    BattleHelper _helper;
    robot_id_t _robot_id;
    std::vector<std::vector<std::string>> _script;
    std::vector<std::string> _script_unsplitted;
    size_t _current_line;
    size_t _branch_depth;
    size_t current_depth;
    bool _executing;

    bool line_is_command();
    bool line_evaluate_expr();
    size_t line_size();
    std::string& get_word(size_t index);
    Command get_command();
    void next_line();

public:
    Interpret(const std::string& filename, robot_id_t robot_id,
        std::array<std::array<FieldObject, FIELD_SIZE>, FIELD_SIZE>* battlefield,
        std::array<std::array<robot_id_t, FIELD_SIZE>, FIELD_SIZE>* robots_on_field,
        std::map<robot_id_t, Robot>* robots);
    Command next_command();
};

inline void Interpret::next_line()
{
    _current_line = (_current_line + 1) % _script.size();
}

#endif
