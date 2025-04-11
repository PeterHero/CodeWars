#ifndef rotation_hpp_
#define rotation_hpp_

#include <string>

#define ROTATION_LEFT "left"
#define ROTATION_RIGHT "right"

enum class Rotation { LEFT,
    RIGHT };

inline bool is_rotation(std::string str)
{
    return str == ROTATION_LEFT || str == ROTATION_RIGHT;
}

Rotation string_to_rotation(std::string str)
{
    if (str == ROTATION_LEFT)
        return Rotation::LEFT;
    else
        return Rotation::RIGHT;
}

#endif