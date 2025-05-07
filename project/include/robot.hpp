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

class Robot {
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

    Interpreter* get_control_script() const { return _control_script.get(); };
    void set_control_script(std::unique_ptr<Interpreter> control_script) { _control_script = std::move(control_script); }

    battlefield_t* get_battlefield_ptr() const { return _battlefield_ptr; }
    void set_battlefield_ptr(battlefield_t* battlefield_ptr) { _battlefield_ptr = battlefield_ptr; }

    robotfield_t* get_robotfield_ptr() const { return _robotfield_ptr; }
    void set_robotfield_ptr(robotfield_t* robotfield_ptr) { _robotfield_ptr = robotfield_ptr; }

    std::map<robot_id_t, Robot>* get_robots_ptr() const { return _robots_ptr; }
    void set_robots_ptr(std::map<robot_id_t, Robot>* robots_ptr) { _robots_ptr = robots_ptr; }

    robot_id_t get_id() const { return _id; }
    void set_id(robot_id_t id) { _id = id; }

    size_t get_team_id() const { return _team_id; }
    void set_team_id(size_t team_id) { _team_id = team_id; }

    size_t get_health() const { return _health; }
    void set_health(size_t health) { _health = health; }

    size_t get_pos_x() const { return _pos_x; }
    void set_pos_x(size_t pos_x) { _pos_x = pos_x; }

    size_t get_pos_y() const { return _pos_y; }
    void set_pos_y(size_t pos_y) { _pos_y = pos_y; }

    Direction get_look_dir() const { return _look_dir; }
    void set_look_dir(Direction look_dir) { _look_dir = look_dir; }

    bool get_is_alive() const { return _is_alive; }
    void set_is_alive(bool is_alive) { _is_alive = is_alive; }

    size_t get_points() const { return _points; }
    void set_points(size_t points) { _points = points; }

    Bomb* get_bomb() const { return _bomb; }
    void set_bomb(Bomb* bomb) { _bomb = bomb; }

    /* Other */
    explicit operator bool() const { return _is_alive; }
    void print(std::ostream& stream) const;
};

std::ostream& operator<<(std::ostream& stream, Robot& robot);

#endif
