#ifndef interpreter_hpp_
#define interpreter_hpp_

#include "command.hpp"
#include "robot_info.hpp"
#include <memory>
#include <vector>

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

class Interpreter {
private:
    RobotInfo* _robot;
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
    std::unique_ptr<Command> get_command();
    void next_line();

public:
    Interpreter(std::string filename, RobotInfo* robot);
    std::unique_ptr<Command> next_command();
};

#endif