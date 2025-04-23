#include "battle_controller.hpp"
#include "field_objects.hpp"
#include <iostream>
#include <set>

BattleController::BattleController(GAME_MODE game_mode)
    : _game_mode(game_mode)
{
    srand(time(NULL));
}

void BattleController::create_robot(robot_id_t id, size_t team_id, Direction direction, std::string script_file)
{
    size_t pos_x, pos_y;
    get_free_field(pos_x, pos_y);
    auto interpreter = std::make_unique<Interpreter>(script_file);
    _robots_storage[id] = Robot(id, team_id, pos_x, pos_y, direction, std::move(interpreter), &_battlefield, &_robotfield, &_robots_storage);
    _robotfield[pos_x][pos_y] = id;
    _robots.push_back(&_robots_storage[id]);
}

void BattleController::create_object(std::unique_ptr<FieldObject> object)
{
    size_t pos_x, pos_y;
    get_free_field(pos_x, pos_y);
    _battlefield[pos_x][pos_y] = std::move(object);
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

void BattleController::setup_robots(std::vector<std::string>& scripts, size_t number_of_teams, size_t robots_in_team)
{
    _robotfield = robotfield_t();
    for (auto&& row : _robotfield)
        for (auto&& id : row)
            id = ROBOT_NULL_ID;
    _robots = std::vector<Character*>();

    size_t id = 1;
    size_t script_index = 0;
    for (size_t team_id = 0; team_id < number_of_teams; ++team_id) {
        for (size_t i = 0; i < robots_in_team; ++i) {
            create_robot(id++, team_id, Direction::UP, scripts[script_index]);
            script_index = (script_index + 1) % scripts.size();
        }
    }
}

void BattleController::setup_battlefield()
{
    _battlefield = battlefield_t();
    for (auto&& row : _battlefield) {
        for (size_t i = 0; i < row.size(); ++i) {
            row[i] = std::make_unique<Ground>();
        }
    }

    create_objects<Point>(4);
    create_objects<Box>(4);
    create_objects<Wall>(2);
}

void BattleController::refresh_battlefield()
{
    for (auto&& row : _battlefield)
        for (auto&& object : row)
            object->turn_refresh();
}

size_t BattleController::teams_alive()
{
    std::set<size_t> teams;
    for (auto&& robot_ptr : _robots)
        teams.insert(robot_ptr->team_id());

    return teams.size();
}

void BattleController::get_free_field(size_t& pos_x, size_t& pos_y)
{
    int random = rand() % (FIELD_SIZE * FIELD_SIZE);
    pos_x = random / FIELD_SIZE;
    pos_y = random % FIELD_SIZE;
    while (_battlefield[pos_x][pos_y]->get_type() != Ground {}.get_type() && _robotfield[pos_x][pos_y] == ROBOT_NULL_ID) {
        int random = rand() % (FIELD_SIZE * FIELD_SIZE);
        pos_x = random / FIELD_SIZE;
        pos_y = random % FIELD_SIZE;
    }
}

void BattleController::simulate_battle()
{
    print_battlefield();

    int turns = TURNS_MAX;
    while (turns > 0) {
        turns--;

        if (teams_alive() <= 1)
            break;

        for (auto&& robot_ptr : _robots)
            if (robot_ptr->is_alive())
                robot_ptr->act();

        print_battlefield();
        update_robots();
        refresh_battlefield();
    }

    std::cout << std::endl
              << std::endl
              << "END OF BATTLE!" << std::endl
              << std::endl;

    if (_game_mode == GAME_MODE::DEATHMATCH) {
        std::cout << "Robots alive are:" << std::endl;
        for (auto&& robot : _robots) {
            std::cout << "R[" << robot->id() << "] (" << robot->script_file() << ")" << std::endl;
        }
    } else if (_game_mode == GAME_MODE::TEAM_DM) {
        std::cout << "Robots alive are:" << std::endl;
        for (auto&& robot : _robots) {
            std::cout << "T[" << robot->team_id() << "]R[" << robot->id() << "] (" << robot->script_file() << ")" << std::endl;
        }
    } else if (_game_mode == GAME_MODE::POINTS) {
        auto cmp = [](Character* a, Character* b) { return a->points() > b->points(); };
        std::set<Character*, decltype(cmp)> scoreboard;

        for (auto&& robot : _robots)
            scoreboard.insert(robot);

        size_t ranking = 1;
        for (auto&& robot : scoreboard) {
            std::cout << ranking++ << ". R[" << robot->id() << "] -> " << robot->points() << "p (" << robot->script_file() << ")" << std::endl;
        }
    }
}