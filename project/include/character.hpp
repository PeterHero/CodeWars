#ifndef character_hpp_
#define character_hpp_

#include <cstddef>
#include <string>
using robot_id_t = size_t;

class Character {
public:
    virtual void act() = 0;
    virtual bool is_alive() = 0;
    virtual robot_id_t id() = 0;
    virtual size_t team_id() = 0;
    virtual size_t points() = 0;
    virtual std::string script_file() = 0;
    virtual ~Character() { };
};

#endif