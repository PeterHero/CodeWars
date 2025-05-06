#ifndef command_factory_hpp_
#define command_factory_hpp_

#include "commands.hpp"
#include "robot_info.hpp"
#include <memory>
#include <string>
#include <vector>

class CommandFactory {
public:
    static std::unique_ptr<Command> create(const std::vector<std::string>& line, RobotInfo& robot);
};

#endif