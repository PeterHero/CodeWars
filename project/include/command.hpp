#ifndef command_hpp_
#define command_hpp_

#include "robot_actions.hpp"

class Command {
public:
    virtual void execute(RobotActions& robot) = 0;
    virtual ~Command() { };
};

#endif