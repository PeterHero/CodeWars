// #include "robot.hpp"
#include "../include/robot.hpp"

Robot::Robot()
    : _is_alive(false)
{
}

Robot::Robot(robot_id_t id,
    size_t pos_x,
    size_t pos_y,
    Direction direction,
    std::unique_ptr<Interpreter> control_script,
    battlefield_t* battlefield_ptr,
    robotfield_t* robotfield_ptr)
    : _id(id)
    , _health(ROBOT_MAX_HEALTH)
    , _pos_x(pos_x)
    , _pos_y(pos_y)
    , _look_dir(direction)
    , _control_script(std::move(control_script))
    , _battlefield_ptr(battlefield_ptr)
    , _robotfield_ptr(robotfield_ptr)
    , _is_alive(true)
    , _points(0)
{
}

/* Character interface */

void Robot::act()
{
    _control_script->next_command()->execute(*this);
}

/* RobotActions interface*/

void Robot::shoot()
{
    size_t bullet_x = _pos_x;
    size_t bullet_y = _pos_y;
    while (calc_position(bullet_x, bullet_y, _look_dir, bullet_x, bullet_y)) {
        Robot& r = _robotfield_ptr->at(bullet_x)[bullet_y];
        if (r) {
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
        if (!_robotfield_ptr->at(new_x)[new_y] && _battlefield_ptr->at(new_x)[new_y]->is_walkable()) {
            std::swap(_robotfield_ptr->at(_pos_x)[_pos_y], _robotfield_ptr->at(new_x)[new_y]);
            _pos_x = new_x;
            _pos_y = new_y;

            _battlefield_ptr->at(new_x)[new_y]->on_step_action(*this);
        }
    }
}

void Robot::turn(Rotation rotation)
{
    if (rotation == Rotation::LEFT) {
        switch (_look_dir) {
        case Direction::LEFT:
            _look_dir = Direction::DOWN;
            break;
        case Direction::DOWN:
            _look_dir = Direction::RIGHT;
            break;
        case Direction::RIGHT:
            _look_dir = Direction::UP;
            break;
        case Direction::UP:
            _look_dir = Direction::LEFT;
            break;
        }
    } else {
        switch (_look_dir) {
        case Direction::LEFT:
            _look_dir = Direction::UP;
            break;
        case Direction::UP:
            _look_dir = Direction::RIGHT;
            break;
        case Direction::RIGHT:
            _look_dir = Direction::DOWN;
            break;
        case Direction::DOWN:
            _look_dir = Direction::LEFT;
            break;
        }
    }
}

void Robot::place_bomb()
{
    // todo implement
}

/* RobotEvents interface */

void Robot::heal()
{
    _health = ROBOT_MAX_HEALTH;
}

void Robot::take_damage(size_t damage)
{
    _health = (_health > damage) ? _health - damage : 0;
    _is_alive = _health > 0;
}

void Robot::collect_point()
{
    _points++;
}

/* RobotInfo interface */

bool Robot::sees_enemy()
{
    size_t x = _pos_x;
    size_t y = _pos_y;
    while (calc_position(x, y, _look_dir, x, y)) {
        if (_robotfield_ptr->at(x)[y])
            return true;
    }
    return false;
}

bool Robot::sees(FieldObject* object)
{
    size_t x = _pos_x;
    size_t y = _pos_y;
    while (calc_position(x, y, _look_dir, x, y)) {
        if (_battlefield_ptr->at(x)[y]->get_type() == object->get_type())
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

    if (_robotfield_ptr->at(x)[y])
        return false;

    return _battlefield_ptr->at(x)[y]->is_walkable();
}

bool Robot::can_place_bomb()
{
    Direction back = opposite_direction(_look_dir);
    size_t x;
    size_t y;
    if (!calc_position(_pos_x, _pos_y, back, x, y))
        return false;

    if (!_battlefield_ptr->at(x)[y]->is_empty())
        return false;

    if (_robotfield_ptr->at(x)[y])
        return false;

    return true;
}

bool Robot::is_low_health()
{
    return _health < ROBOT_MAX_HEALTH / 2;
}