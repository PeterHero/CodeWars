#include "declarations.hpp"

BattleHelper::BattleHelper(std::array<std::array<FieldObject, FIELD_SIZE>, FIELD_SIZE>* battlefield,
    std::array<std::array<robot_id_t, FIELD_SIZE>, FIELD_SIZE>* robots_on_field,
    std::map<robot_id_t, Robot>* robots)
    : _battlefield(battlefield)
    , _robots_on_field(robots_on_field)
    , _robots(robots)
{
}

bool BattleHelper::robot_sees_enemy(robot_id_t id)
{
    const Robot& robot = _robots->at(id);

    size_t pos_x = robot.get_x();
    size_t pos_y = robot.get_y();
    while (calc_position(pos_x, pos_y, robot.get_look_dir(), pos_x, pos_y)) {
        if (_robots_on_field->at(pos_x)[pos_y] != ROBOT_NULL_ID)
            return true;
    }
    return false;
}