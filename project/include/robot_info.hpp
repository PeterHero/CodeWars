#ifndef robot_info_hpp_
#define robot_info_hpp_

#include "direction.hpp"
#include "field_object.hpp"

class RobotInfo {
public:
    virtual bool sees_enemy() = 0;
    virtual bool sees(FieldObject object) = 0;
    virtual bool can_move(Direction direction) = 0;
    virtual bool can_place_bomb() = 0;
    virtual bool is_low_health() = 0;
    virtual ~RobotInfo() { };
};

#endif