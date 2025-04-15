#include "rotation.hpp"

bool is_rotation(std::string str)
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