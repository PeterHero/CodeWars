#include "command_factory.hpp"
#include "plog/Log.h"

std::unique_ptr<Command> CommandFactory::create(const std::vector<std::string>& line, RobotInfo& robot)
{
    if (line.size() < 3 || line[0] != "robot" || line[1] != "cmd") {
        PLOG_ERROR << "Invalid command format";
        return std::make_unique<CommandMove>(Direction::UP);
    }

    const std::string& cmd = line[2];
    if (cmd == "shoot") {
        return std::make_unique<CommandShoot>();
    } else if (cmd == "move" && line.size() == 4) {
        if (is_direction(line[3]))
            return std::make_unique<CommandMove>(string_to_direction(line[3], robot.look_direction()));
        else
            PLOG_ERROR << line[3] << " is not a valid direction";
    } else if (cmd == "turn" && line.size() == 4) {
        if (is_rotation(line[3]))
            return std::make_unique<CommandTurn>(string_to_rotation(line[3]));
        else
            PLOG_ERROR << line[3] << " in not a valid rotation";
    } else if (cmd == "place" && line[3] == "bomb") {
        return std::make_unique<CommandPlaceBomb>();
    } else {
        PLOG_ERROR << "Invalid command!";
    }
    return std::make_unique<CommandMove>(Direction::UP);
}