#ifndef interpreter_hpp_
#define interpreter_hpp_

#include "command.hpp"
#include "robot_info.hpp"

class Interpreter {
public:
    Interpreter(std::string filename, RobotInfo* robot);
    Command next_command();
};

#endif