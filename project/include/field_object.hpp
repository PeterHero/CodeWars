#ifndef field_object_hpp_
#define field_object_hpp_

#include "robot_events.hpp"
#include <string>

class FieldObject {
public:
    virtual std::string get_type() = 0;
    virtual bool is_walkable() = 0;
    virtual bool is_bullet_passable() = 0;
    virtual void on_step_action(RobotEvents& robot) = 0;
    virtual FieldObject on_shoot_action() = 0;

    virtual ~FieldObject() { };
};
;

#endif