#ifndef direction_hpp_
#define direction_hpp_

#include <cstddef>

enum class Direction { LEFT,
    UP,
    RIGHT,
    DOWN };

bool calc_position(size_t old_x, size_t old_y, Direction direction, size_t& new_x, size_t& new_y);

#endif