#ifndef robot_logic_hpp_
#define robot_logic_hpp_

#include "character.hpp"
#include "robot.hpp"
#include "robot_actions.hpp"
#include "robot_events.hpp"
#include "robot_info.hpp"

class RobotLogic : public Character, public RobotActions, public RobotEvents, public RobotInfo {
private:
    Robot* _data;

    void deal_bomb_damage(size_t& pos_x, size_t& pos_y, Direction direction);

public:
    RobotLogic(Robot* robot_ptr);

    /* Character interface */

    void act() override;
    bool is_alive() override;
    robot_id_t id() override;
    size_t team_id() override;
    size_t points() override;
    std::string script_file() override;

    /* RobotActions interface*/

    void shoot() override;
    void move(Direction direction) override;
    void turn(Rotation rotation) override;
    void place_bomb() override;

    /* RobotEvents interface */

    void heal() override;
    void take_damage(size_t damage) override;
    void collect_point() override;
    void explode_bomb() override;

    /* RobotInfo interface */

    bool sees_enemy() override;
    bool sees(std::string object_string) override;
    bool can_move(Direction direction) override;
    bool can_place_bomb() override;
    bool is_low_health() override;
    Direction look_direction() override;
};

#endif