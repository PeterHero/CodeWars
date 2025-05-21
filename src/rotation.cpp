#include "rotation.hpp"

/**
 * @brief Checks if string is valid Rotation
 *
 * @param str string to check
 * @return true if string is valid Rotation
 * @return false otherwise
 */
bool is_rotation(std::string str)
{
    return str == ROTATION_LEFT || str == ROTATION_RIGHT;
}

/**
 * @brief Creates Rotations from string
 *
 * @param str Source string
 * @return Rotation
 */
Rotation string_to_rotation(std::string str)
{
    if (str == ROTATION_LEFT)
        return Rotation::LEFT;
    else
        return Rotation::RIGHT;
}