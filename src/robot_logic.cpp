#include "robot_logic.hpp"

RobotLogic::RobotLogic(Robot* robot_ptr)
    : _data(robot_ptr)
{
}

/* Character interface */

/**
 * @brief Execute next command
 *
 */
void RobotLogic::act()
{
    PLOG_VERBOSE << "Robot " << _data->get_id() << " turn:";
    _data->get_control_script()->next_command(*this)->execute(*this);
    if (_data->get_bomb()) {
        _data->get_bomb()->tick();
    }
}

/**
 * @brief Checks if robot is alive
 *
 * @return true
 * @return false
 */
bool RobotLogic::is_alive()
{
    return _data->get_is_alive();
}

/**
 * @brief Get robot id
 *
 * @return robot_id_t
 */
robot_id_t RobotLogic::id()
{
    return _data->get_id();
}

/**
 * @brief Get robot team id
 *
 * @return size_t
 */
size_t RobotLogic::team_id()
{
    return _data->get_team_id();
}

/**
 * @brief Get robot points
 *
 * @return size_t
 */
size_t RobotLogic::points()
{
    return _data->get_points();
}

/**
 * @brief Get robot script filename
 *
 * @return std::string
 */
std::string RobotLogic::script_file()
{
    return _data->get_control_script()->_filename;
}

/* RobotActions interface*/

/**
 * @brief Fire a bullet which finds a target until it stops or goes beyond battlefield
 *
 */
void RobotLogic::shoot()
{
    PLOG_WARNING << "R[" << _data->get_id() << "]: Shot a bullet";

    size_t bullet_x = _data->get_pos_x();
    size_t bullet_y = _data->get_pos_y();
    while (calc_position(bullet_x, bullet_y, _data->get_look_dir(), bullet_x, bullet_y)) {
        if (_data->get_robotfield_ptr()->at(bullet_x)[bullet_y] != ROBOT_NULL_ID) {
            Robot& r = _data->get_robots_ptr()->at(_data->get_robotfield_ptr()->at(bullet_x)[bullet_y]);
            RobotLogic(&r).take_damage(SHOT_DAMAGE);
            break;
        }

        auto&& object = _data->get_battlefield_ptr()->at(bullet_x)[bullet_y];
        if (!object->is_bullet_passable()) {
            _data->get_battlefield_ptr()->at(bullet_x)[bullet_y] = std::move(object->on_shoot_action(std::move(object)));
            break;
        }
    }
}

/**
 * @brief Move robot in the direction if can move
 *
 * @param direction
 */
void RobotLogic::move(Direction direction)
{
    size_t new_x;
    size_t new_y;
    if (calc_position(_data->get_pos_x(), _data->get_pos_y(), _data->get_look_dir(), new_x, new_y)) {
        if (_data->get_robotfield_ptr()->at(new_x)[new_y] == ROBOT_NULL_ID && _data->get_battlefield_ptr()->at(new_x)[new_y]->is_walkable()) {
            robot_id_t old = _data->get_robotfield_ptr()->at(_data->get_pos_x())[_data->get_pos_y()];
            _data->get_robotfield_ptr()->at(_data->get_pos_x())[_data->get_pos_y()] = _data->get_robotfield_ptr()->at(new_x)[new_y];
            _data->get_robotfield_ptr()->at(new_x)[new_y] = old;
            _data->set_pos_x(new_x);
            _data->set_pos_y(new_y);

            _data->get_battlefield_ptr()->at(new_x)[new_y]->on_step_action(*this);

            PLOG_WARNING << "R[" << _data->get_id() << "]: Moved " << to_string(direction);
        }
    }
}

/**
 * @brief Turn robot according to rotation
 *
 * @param rotation
 */
void RobotLogic::turn(Rotation rotation)
{

    if (rotation == Rotation::LEFT) {
        _data->set_look_dir(left_direction(_data->get_look_dir()));
        PLOG_WARNING << "R[" << _data->get_id() << "]: Turned left";
    } else {
        _data->set_look_dir(right_direction(_data->get_look_dir()));
        PLOG_WARNING << "R[" << _data->get_id() << "]: Turned right";
    }
}

/**
 * @brief Place a bomb behind robot if the spot is empty
 *
 */
void RobotLogic::place_bomb()
{
    Direction back = opposite_direction(_data->get_look_dir());
    size_t bomb_x;
    size_t bomb_y;
    calc_position(_data->get_pos_x(), _data->get_pos_y(), opposite_direction(_data->get_look_dir()), bomb_x, bomb_y);
    if (can_place_bomb()) {
        _data->get_battlefield_ptr()->at(bomb_x)[bomb_y] = std::make_unique<Bomb>(this, bomb_x, bomb_y);
        _data->set_bomb((Bomb*)_data->get_battlefield_ptr()->at(bomb_x)[bomb_y].get());
        PLOG_WARNING << "R[" << _data->get_id() << "]: Placed a bomb";
    }
}

/* RobotEvents interface */

/**
 * @brief Heal to full health
 *
 */
void RobotLogic::heal()
{
    _data->set_health(ROBOT_MAX_HEALTH);
    PLOG_WARNING << "R[" << _data->get_id() << "]: Healed";
}

/**
 * @brief Take amount of damage
 *
 * @param damage damage to be taken
 */
void RobotLogic::take_damage(size_t damage)
{
    PLOG_WARNING << "R[" << _data->get_id() << "]: Was damaged with " << damage;

    _data->set_health((_data->get_health() > damage) ? _data->get_health() - damage : 0);
    _data->set_is_alive(_data->get_health() > 0);
    if (!_data->get_is_alive()) {
        _data->get_robotfield_ptr()->at(_data->get_pos_x())[_data->get_pos_y()] = ROBOT_NULL_ID;
        PLOG_WARNING << "R[" << _data->get_id() << "]: Is dead";
    }
}

/**
 * @brief Collect a point
 *
 */
void RobotLogic::collect_point()
{
    _data->set_points(_data->get_points() + 1);
    PLOG_WARNING << "R[" << _data->get_id() << "]: Collected a point";
}

/**
 * @brief Deal bomb damage in the position using direction
 *
 * @param pos_x x coordinate, return value for new position
 * @param pos_y y coordinate, return value for new position
 * @param direction direction in which to deal damage
 */
void RobotLogic::deal_bomb_damage(size_t& pos_x, size_t& pos_y, Direction direction)
{
    if (calc_position(pos_x, pos_y, direction, pos_x, pos_y) && _data->get_robotfield_ptr()->at(pos_x)[pos_y] != ROBOT_NULL_ID) {
        Robot& r = _data->get_robots_ptr()->at(_data->get_robotfield_ptr()->at(pos_x)[pos_y]);
        RobotLogic(&r).take_damage(BOMB_DAMAGE);
    }
}

/**
 * @brief Deal damage in an area around bomb
 *
 */
void RobotLogic::explode_bomb()
{
    PLOG_WARNING << "R[" << _data->get_id() << "]: Bomb has exploded";

    size_t x = _data->get_bomb()->pos_x;
    size_t y = _data->get_bomb()->pos_y;

    // deal area damage
    deal_bomb_damage(x, y, Direction::UP);
    deal_bomb_damage(x, y, Direction::RIGHT);
    deal_bomb_damage(x, y, Direction::DOWN);
    deal_bomb_damage(x, y, Direction::DOWN);
    deal_bomb_damage(x, y, Direction::LEFT);
    deal_bomb_damage(x, y, Direction::LEFT);
    deal_bomb_damage(x, y, Direction::UP);
    deal_bomb_damage(x, y, Direction::UP);

    _data->get_battlefield_ptr()->at(_data->get_bomb()->pos_x)[_data->get_bomb()->pos_y] = std::make_unique<Ground>();
    _data->set_bomb(nullptr);
}

/* RobotInfo interface */

/**
 * @brief Checks if robot sees enemy
 *
 * @return true
 * @return false
 */
bool RobotLogic::sees_enemy()
{
    size_t x = _data->get_pos_x();
    size_t y = _data->get_pos_y();
    while (calc_position(x, y, _data->get_look_dir(), x, y)) {
        robot_id_t id = _data->get_robotfield_ptr()->at(x)[y];
        if (id != ROBOT_NULL_ID)
            return _data->get_robots_ptr()->at(id).get_team_id() != _data->get_team_id();
    }
    return false;
}

/**
 * @brief Checks if robot sees an object
 *
 * @param object_string object type in string
 * @return true
 * @return false
 */
bool RobotLogic::sees(std::string object_string)
{
    size_t x = _data->get_pos_x();
    size_t y = _data->get_pos_y();
    while (calc_position(x, y, _data->get_look_dir(), x, y)) {
        if (_data->get_battlefield_ptr()->at(x)[y]->get_type() == object_string)
            return true;
    }
    return false;
}

/**
 * @brief Checks if robot can move in direction
 *
 * @param direction
 * @return true
 * @return false
 */
bool RobotLogic::can_move(Direction direction)
{
    size_t x;
    size_t y;
    if (!calc_position(_data->get_pos_x(), _data->get_pos_y(), _data->get_look_dir(), x, y))
        return false;

    if (_data->get_robotfield_ptr()->at(x)[y] != ROBOT_NULL_ID)
        return false;

    return _data->get_battlefield_ptr()->at(x)[y]->is_walkable();
}

/**
 * @brief Checks if robot can place bomb behind it
 *
 * @return true
 * @return false
 */
bool RobotLogic::can_place_bomb()
{
    if (_data->get_bomb() != nullptr)
        return false;

    Direction back = opposite_direction(_data->get_look_dir());
    size_t x;
    size_t y;
    if (!calc_position(_data->get_pos_x(), _data->get_pos_y(), back, x, y))
        return false;

    if (!_data->get_battlefield_ptr()->at(x)[y]->is_empty())
        return false;

    if (_data->get_robotfield_ptr()->at(x)[y] != ROBOT_NULL_ID)
        return false;

    return true;
}

/**
 * @brief Checks if robot health is below treshold
 *
 * @return true
 * @return false
 */
bool RobotLogic::is_low_health()
{
    return _data->get_health() < ROBOT_MAX_HEALTH / 2;
}

/**
 * @brief Get robot look direction
 *
 * @return Direction
 */
Direction RobotLogic::look_direction()
{
    return _data->get_look_dir();
}