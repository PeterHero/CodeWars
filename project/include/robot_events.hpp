#ifndef robot_events_hpp_
#define robot_events_hpp_

#include <cstddef>

class RobotEvents {
public:
    virtual void heal() = 0;
    virtual void take_damage(size_t damage) = 0;
    virtual void collect_point() = 0;
    virtual ~RobotEvents() { }
};

#endif