#ifndef battle_helper_hpp_
#define battle_helper_hpp_

#include "direction.hpp"
#include <array>
#include <map>

class FieldObject;
using robot_id_t = size_t;
class Robot;

class BattleHelper {
private:
    const std::array<std::array<FieldObject, FIELD_SIZE>, FIELD_SIZE>* _battlefield;
    const std::array<std::array<robot_id_t, FIELD_SIZE>, FIELD_SIZE>* _robots_on_field;
    const std::map<robot_id_t, Robot>* _robots;

public:
    BattleHelper(std::array<std::array<FieldObject, FIELD_SIZE>, FIELD_SIZE>* battlefield,
        std::array<std::array<robot_id_t, FIELD_SIZE>, FIELD_SIZE>* robots_on_field,
        std::map<robot_id_t, Robot>* robots);

    bool robot_sees_enemy(robot_id_t robot);
};

#endif
