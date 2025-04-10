#ifndef robot_hpp_
#define robot_hpp_

#include "robot_actions.hpp"
#include "robot_events.hpp"
#include "robot_info.hpp"

class Robot : public RobotActions, public RobotEvents, public RobotInfo {
};

#endif