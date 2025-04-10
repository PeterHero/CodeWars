#ifndef robot_actions_hpp_
#define robot_actions_hpp_

#include "direction.hpp"

class RobotActions {
public:
    virtual void shoot() = 0;
    virtual void move(Direction direction) = 0;
    virtual void turn_left() = 0;
    virtual void turn_right() = 0;
    virtual void place_bomb() = 0;
    virtual ~RobotActions() { };
};

#endif