#ifndef robot_hpp_
#define robot_hpp_

#include "character.hpp"
#include "field_objects.hpp"
#include "interpreter.hpp"
#include "robot_actions.hpp"
#include "robot_events.hpp"
#include "robot_info.hpp"
#include <array>
#include <map>
#include <memory>

#define ROBOT_MAX_HEALTH 100
#define SHOT_DAMAGE 50
#define BOMB_DAMAGE 50
#define ROBOT_NULL_ID 0

class Robot;

using robot_id_t = size_t;
using battlefield_t = std::array<std::array<std::unique_ptr<FieldObject>, FIELD_SIZE>, FIELD_SIZE>;
using robotfield_t = std::array<std::array<robot_id_t, FIELD_SIZE>, FIELD_SIZE>;

class Robot : public Character, public RobotActions, public RobotEvents, public RobotInfo {
private:
    std::unique_ptr<Interpreter> _control_script;
    battlefield_t* _battlefield_ptr;
    robotfield_t* _robotfield_ptr;
    std::map<robot_id_t, Robot>* _robots_ptr;
    robot_id_t _id;
    size_t _team_id;
    size_t _health;
    size_t _pos_x;
    size_t _pos_y;
    Direction _look_dir;
    bool _is_alive;
    size_t _points;
    Bomb* _bomb;

    void deal_bomb_damage(size_t& pos_x, size_t& pos_y, Direction direction);

public:
    Robot();
    Robot(robot_id_t id,
        size_t team_id,
        size_t pos_x,
        size_t pos_y,
        Direction direction,
        std::unique_ptr<Interpreter> control_script,
        battlefield_t* battlefield_ptr,
        robotfield_t* robotfield_ptr,
        std::map<robot_id_t, Robot>* robots);

    /* Character interface */

    void act() override;
    bool is_alive() override;
    robot_id_t id() override;
    size_t team_id() override;

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

    /* Other */
    explicit operator bool() const { return _is_alive; }
    void print(std::ostream& stream) const;
};

std::ostream& operator<<(std::ostream& stream, Robot& robot);

#endif
