#ifndef rotation_hpp_
#define rotation_hpp_

#include <string>

#define ROTATION_LEFT "left"
#define ROTATION_RIGHT "right"

enum class Rotation { LEFT,
    RIGHT };

bool is_rotation(std::string str);

Rotation string_to_rotation(std::string str);

#endif