#include "battle_controller.hpp"
#include "robot.hpp"
#include <iostream>
#include <plog/Log.h>

BattleController::BattleController()
    : _robots_on_field({})
    , _battlefield({})
{
    _battlefield[0][1] = FieldObject(FieldObject::Type::WALL);
    _battlefield[1][2] = FieldObject(FieldObject::Type::HEAL);

    create_robot(1, 0, 0, Direction::RIGHT, "examples/test.rbsh");
    create_robot(2, 1, 1, Direction::RIGHT, "examples/test.rbsh");
    create_robot(3, 3, 3, Direction::LEFT, "examples/test.rbsh");
    create_robot(4, 4, 4, Direction::LEFT, "examples/test.rbsh");

    print_battlefield();
}

void BattleController::create_robot(robot_id_t id, size_t pos_x, size_t pos_y, Direction direction, std::string script_file)
{
    _robots[id] = Robot(id, pos_x, pos_y, direction, script_file);
    _robots_on_field[pos_x][pos_y] = id;
}

void BattleController::robot_move(robot_id_t id, Direction direction)
{
    Robot& robot = _robots[id];
    size_t new_x;
    size_t new_y;
    if (calc_position(robot.get_x(), robot.get_y(), direction, new_x, new_y)) {
        if (_robots_on_field[new_x][new_y] == ROBOT_NULL_ID && _battlefield[new_x][new_y].is_walkable()) {
            _robots_on_field[robot.get_x()][robot.get_y()] = ROBOT_NULL_ID;
            _robots_on_field[new_x][new_y] = id;
            robot.set_x(new_x);
            robot.set_y(new_y);
            PLOG_INFO << "Robot " << id << " moved " << to_string(direction);

            if (_battlefield[new_x][new_y].on_step_action(robot)) {
                PLOG_INFO << "Robot " << id << " "
                          << _battlefield[new_x][new_y].get_action_message();
            }
        }
    }
}

void BattleController::robot_shoot(robot_id_t id)
{
    Robot& robot = _robots[id];
    size_t bullet_x = robot.get_x();
    size_t bullet_y = robot.get_y();
    while (calc_position(bullet_x, bullet_y, robot.get_look_dir(), bullet_x,
        bullet_y)) {
        robot_id_t target_id = _robots_on_field[bullet_x][bullet_y];
        if (target_id != ROBOT_NULL_ID) {
            _robots[target_id].get_shot();
            if (_robots[target_id].is_alive()) {
                PLOG_WARNING << "Robot " << id << " shot robot " << target_id;
            } else {
                _robots_on_field[bullet_x][bullet_y] = ROBOT_NULL_ID;
                PLOG_ERROR << "Robot " << id << " killed robot " << target_id;
            }
            break;
        } else if (!_battlefield[bullet_x][bullet_y].is_bullet_passable()) {
            break;
        }
    }
}

void BattleController::robot_turn_left(robot_id_t id)
{
    _robots[id].turn_left();
    PLOG_INFO << "Robot " << id << " turned left";
}

void BattleController::robot_turn_right(robot_id_t id)
{
    _robots[id].turn_right();
    PLOG_INFO << "Robot " << id << " turned right";
}

void BattleController::print_battlefield()
{
    for (size_t i = 0; i < FIELD_SIZE + 2; ++i)
        std::cout << "X";
    std::cout << std::endl;

    for (size_t i = 0; i < FIELD_SIZE; ++i) {
        size_t y = FIELD_SIZE - 1 - i;
        std::cout << "X";
        for (size_t x = 0; x < FIELD_SIZE; ++x) {
            robot_id_t robot_id = _robots_on_field[x][y];
            if (robot_id == ROBOT_NULL_ID) {
                std::cout << _battlefield[x][y];
            } else {
                std::cout << _robots[robot_id];
            }
        }
        std::cout << "X" << std::endl;
    }

    for (size_t i = 0; i < FIELD_SIZE + 2; ++i)
        std::cout << "X";
    std::cout << std::endl;
}

void BattleController::execute_command(robot_id_t id, const Command& cmd)
{
    switch (cmd.type) {
    case Command::Type::SHOOT:
        robot_shoot(id);
        break;
    case Command::Type::TURN_LEFT:
        robot_turn_left(id);
        break;
    case Command::Type::TURN_RIGHT:
        robot_turn_right(id);
        break;
    case Command::Type::MOVE:
        robot_move(id, cmd.move_direction);
        break;
    case Command::Type::INVALID:
        // todo print error
        break;
    }
}

void BattleController::simulate_battle()
{
    for (size_t turn = 0; turn < TURNS_MAX; ++turn) {
        if (_robots.size() == 1) {
            break;
        }

        for (auto& [id, robot] : _robots) {
            if (robot.is_alive()) {
                Command cmd = robot.control_script.next_command();
                execute_command(id, cmd);
            }
        }

        for (auto it = _robots.cbegin(); it != _robots.cend();) {
            if (it->second.is_alive()) {
                ++it;
            } else {
                _scoreboard.push_back(it->first);
                it = _robots.erase(it);
            }
        }

        print_battlefield();
    }

    std::cout << "Stayin' alive: ";
    for (auto const& [id, robot] : _robots) {
        std::cout << id << " ";
    }
    std::cout << std::endl;
}
