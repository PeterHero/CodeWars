#include "battle_controller.hpp"
#include "field_objects.hpp"
#include <iostream>

void BattleController::create_robot(robot_id_t id, size_t pos_x, size_t pos_y, Direction direction, std::string script_file)
{
    auto interpreter = std::make_unique<Interpreter>(script_file);
    _robots_storage[id] = Robot(id, pos_x, pos_y, direction, std::move(interpreter), &_battlefield, &_robotfield, &_robots_storage);
    _robotfield[pos_x][pos_y] = id;
    _robots.push_back(&_robots_storage[id]);
}

void BattleController::update_robots()
{
    _robots = std::vector<Character*>();
    for (auto&& row : _robotfield)
        for (auto&& robot_id : row)
            if (_robots_storage[robot_id].is_alive())
                _robots.push_back(&_robots_storage[robot_id]);
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
            if (_robotfield[x][y] != ROBOT_NULL_ID)
                std::cout << _robots_storage[_robotfield[x][y]];
            else
                _battlefield[x][y]->print();
        }
        std::cout << "X" << std::endl;
    }

    for (size_t i = 0; i < FIELD_SIZE + 2; ++i)
        std::cout << "X";
    std::cout << std::endl;
}

void BattleController::setup_robots()
{
    _robotfield = robotfield_t();
    for (auto&& row : _robotfield)
        for (auto&& id : row)
            id = ROBOT_NULL_ID;
    _robots = std::vector<Character*>();

    create_robot(1, 0, 0, Direction::UP, "examples/alpha.rbsh");
    create_robot(2, 1, 1, Direction::UP, "examples/alpha.rbsh");
    create_robot(3, 3, 3, Direction::UP, "examples/simple.rbsh");
    create_robot(4, 4, 4, Direction::UP, "examples/simple.rbsh");
}

void BattleController::setup_battlefield()
{
    _battlefield = battlefield_t();
    for (auto&& row : _battlefield) {
        for (size_t i = 0; i < row.size(); ++i) {
            row[i] = std::make_unique<Ground>();
        }
    }
}

void BattleController::simulate_battle()
{
    print_battlefield();

    int turns = TURNS_MAX;
    while (turns > 0) {
        turns--;

        if (_robots.size() <= 1)
            break;

        for (auto&& robot_ptr : _robots)
            if (robot_ptr->is_alive())
                robot_ptr->act();

        print_battlefield();
        update_robots();
    }
}