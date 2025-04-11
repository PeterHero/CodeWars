#ifndef robot_hpp_
#define robot_hpp_

#include "character.hpp"
#include "robot_actions.hpp"
#include "robot_events.hpp"
#include "robot_info.hpp"

class Robot : public Character, public RobotActions, public RobotEvents, public RobotInfo {
public:
    void bla();
    /* Character interface */
    void act() override;

    /* RobotActions interface*/
    void shoot() override;
    void move(Direction direction) override;
    void turn(Rotation rotation) override;
    void place_bomb() override;

    /* RobotEvents interface */
    void heal() override;
    void take_damage(size_t damage) override;
    void collect_point() override;

    /* RobotInfo interface */
    bool sees_enemy() override;
    bool sees(FieldObject object) override;
    bool can_move(Direction direction) override;
    bool can_place_bomb() override;
    bool is_low_health() override;
};

#endif
