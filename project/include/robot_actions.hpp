#ifndef robot_actions_hpp_
#define robot_actions_hpp_

#include "direction.hpp"

enum class Rotation { LEFT,
    RIGHT };

class RobotActions {
public:
    virtual void shoot() = 0;
    virtual void move(Direction direction) = 0;
    virtual void turn(Rotation rotation) = 0;
    virtual void place_bomb() = 0;
    virtual ~RobotActions() { };
};

#endif