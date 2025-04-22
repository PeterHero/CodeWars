#include "robot.hpp"
#include "field_objects.hpp"
// #include "../include/robot.hpp"
#include <plog/Log.h>

Robot::Robot()
    : _is_alive(false)
{
}

Robot::Robot(robot_id_t id,
    size_t team_id,
    size_t pos_x,
    size_t pos_y,
    Direction direction,
    std::unique_ptr<Interpreter> control_script,
    battlefield_t* battlefield_ptr,
    robotfield_t* robotfield_ptr,
    std::map<robot_id_t, Robot>* robots_ptr)
    : _id(id)
    , _team_id(team_id)
    , _health(ROBOT_MAX_HEALTH)
    , _pos_x(pos_x)
    , _pos_y(pos_y)
    , _look_dir(direction)
    , _control_script(std::move(control_script))
    , _battlefield_ptr(battlefield_ptr)
    , _robotfield_ptr(robotfield_ptr)
    , _robots_ptr(robots_ptr)
    , _is_alive(true)
    , _points(0)
    , _bomb(nullptr)
{
}

/* Character interface */

void Robot::act()
{
    PLOG_VERBOSE << "Robot " << _id << " turn:";
    _control_script->next_command(*this)->execute(*this);
    if (_bomb) {
        _bomb->tick();
    }
}

bool Robot::is_alive()
{
    return _is_alive;
}

robot_id_t Robot::id()
{
    return _id;
}
size_t Robot::team_id()
{
    return _team_id;
}

size_t Robot::points()
{
    return _points;
}

std::string Robot::script_file()
{
    return _control_script->_filename;
}

/* RobotActions interface*/

void Robot::shoot()
{
    PLOG_WARNING << "R[" << _id << "]: Shot a bullet";

    size_t bullet_x = _pos_x;
    size_t bullet_y = _pos_y;
    while (calc_position(bullet_x, bullet_y, _look_dir, bullet_x, bullet_y)) {
        if (_robotfield_ptr->at(bullet_x)[bullet_y] != ROBOT_NULL_ID) {
            Robot& r = _robots_ptr->at(_robotfield_ptr->at(bullet_x)[bullet_y]);
            r.take_damage(SHOT_DAMAGE);
            break;
        }

        auto&& object = _battlefield_ptr->at(bullet_x)[bullet_y];
        if (!object->is_bullet_passable()) {
            _battlefield_ptr->at(bullet_x)[bullet_y] = std::move(object->on_shoot_action(std::move(object)));
            break;
        }
    }
}

void Robot::move(Direction direction)
{
    size_t new_x;
    size_t new_y;
    if (calc_position(_pos_x, _pos_y, _look_dir, new_x, new_y)) {
        if (_robotfield_ptr->at(new_x)[new_y] == ROBOT_NULL_ID && _battlefield_ptr->at(new_x)[new_y]->is_walkable()) {
            robot_id_t old = _robotfield_ptr->at(_pos_x)[_pos_y];
            _robotfield_ptr->at(_pos_x)[_pos_y] = _robotfield_ptr->at(new_x)[new_y];
            _robotfield_ptr->at(new_x)[new_y] = old;
            _pos_x = new_x;
            _pos_y = new_y;

            _battlefield_ptr->at(new_x)[new_y]->on_step_action(*this);

            PLOG_WARNING << "R[" << _id << "]: Moved " << to_string(direction);
        }
    }
}

void Robot::turn(Rotation rotation)
{

    if (rotation == Rotation::LEFT) {
        _look_dir = left_direction(_look_dir);
        PLOG_WARNING << "R[" << _id << "]: Turned left";
    } else {
        _look_dir = right_direction(_look_dir);
        PLOG_WARNING << "R[" << _id << "]: Turned right";
    }
}

void Robot::place_bomb()
{
    Direction back = opposite_direction(_look_dir);
    size_t bomb_x;
    size_t bomb_y;
    calc_position(_pos_x, _pos_y, opposite_direction(_look_dir), bomb_x, bomb_y);
    if (can_place_bomb()) {
        _battlefield_ptr->at(bomb_x)[bomb_y] = std::make_unique<Bomb>(this, bomb_x, bomb_y);
        _bomb = (Bomb*)_battlefield_ptr->at(bomb_x)[bomb_y].get();
        PLOG_WARNING << "R[" << _id << "]: Placed a bomb";
    }
}

/* RobotEvents interface */

void Robot::heal()
{
    _health = ROBOT_MAX_HEALTH;
    PLOG_WARNING << "R[" << _id << "]: Healed";
}

void Robot::take_damage(size_t damage)
{
    PLOG_WARNING << "R[" << _id << "]: Was damaged with " << damage;

    _health = (_health > damage) ? _health - damage : 0;
    _is_alive = _health > 0;
    if (!_is_alive) {
        _robotfield_ptr->at(_pos_x)[_pos_y] = ROBOT_NULL_ID;
        PLOG_WARNING << "R[" << _id << "]: Is dead";
    }
}

void Robot::collect_point()
{
    _points++;
    PLOG_WARNING << "R[" << _id << "]: Collected a point";
}

void Robot::deal_bomb_damage(size_t& pos_x, size_t& pos_y, Direction direction)
{
    if (calc_position(pos_x, pos_y, direction, pos_x, pos_y) && _robotfield_ptr->at(pos_x)[pos_y] != ROBOT_NULL_ID) {
        _robots_ptr->at(_robotfield_ptr->at(pos_x)[pos_y]).take_damage(BOMB_DAMAGE);
    }
}

void Robot::explode_bomb()
{
    PLOG_WARNING << "R[" << _id << "]: Bomb has exploded";

    size_t x = _bomb->pos_x;
    size_t y = _bomb->pos_y;

    // deal area damage
    deal_bomb_damage(x, y, Direction::UP);
    deal_bomb_damage(x, y, Direction::RIGHT);
    deal_bomb_damage(x, y, Direction::DOWN);
    deal_bomb_damage(x, y, Direction::DOWN);
    deal_bomb_damage(x, y, Direction::LEFT);
    deal_bomb_damage(x, y, Direction::LEFT);
    deal_bomb_damage(x, y, Direction::UP);
    deal_bomb_damage(x, y, Direction::UP);

    _battlefield_ptr->at(_bomb->pos_x)[_bomb->pos_y] = std::make_unique<Ground>();
    _bomb = nullptr;
}

/* RobotInfo interface */

bool Robot::sees_enemy()
{
    size_t x = _pos_x;
    size_t y = _pos_y;
    while (calc_position(x, y, _look_dir, x, y)) {
        robot_id_t id = _robotfield_ptr->at(x)[y];
        if (id != ROBOT_NULL_ID)
            return _robots_ptr->at(id).team_id() != _team_id;
    }
    return false;
}

bool Robot::sees(std::string object_string)
{
    size_t x = _pos_x;
    size_t y = _pos_y;
    while (calc_position(x, y, _look_dir, x, y)) {
        if (_battlefield_ptr->at(x)[y]->get_type() == object_string)
            return true;
    }
    return false;
}

bool Robot::can_move(Direction direction)
{
    size_t x;
    size_t y;
    if (!calc_position(_pos_x, _pos_y, _look_dir, x, y))
        return false;

    if (_robotfield_ptr->at(x)[y] != ROBOT_NULL_ID)
        return false;

    return _battlefield_ptr->at(x)[y]->is_walkable();
}

bool Robot::can_place_bomb()
{
    if (_bomb != nullptr)
        return false;

    Direction back = opposite_direction(_look_dir);
    size_t x;
    size_t y;
    if (!calc_position(_pos_x, _pos_y, back, x, y))
        return false;

    if (!_battlefield_ptr->at(x)[y]->is_empty())
        return false;

    if (_robotfield_ptr->at(x)[y] != ROBOT_NULL_ID)
        return false;

    return true;
}

bool Robot::is_low_health()
{
    return _health < ROBOT_MAX_HEALTH / 2;
}

Direction Robot::look_direction()
{
    return _look_dir;
}

void Robot::print(std::ostream& stream) const
{
    switch (_look_dir) {
    case Direction::LEFT:
        stream << std::string("<");
        break;
    case Direction::UP:
        stream << std::string("A");
        break;
    case Direction::RIGHT:
        stream << std::string(">");
        break;
    case Direction::DOWN:
        stream << std::string("V");
        break;
    }
}

std::ostream& operator<<(std::ostream& stream, Robot& robot)
{
    robot.print(stream);
    return stream;
}