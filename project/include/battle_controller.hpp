#ifndef battle_controller_hpp_
#define battle_controller_hpp_

#include "robot.hpp"

#define TURNS_MAX 100

enum class GAME_MODE { DEATHMATCH,
    TEAM_DM,
    POINTS };

class BattleController {
private:
    battlefield_t _battlefield;
    robotfield_t _robotfield;
    std::map<robot_id_t, Robot> _robots_storage;

    std::vector<Character*> _robots;

    size_t _number_of_teams;
    GAME_MODE _game_mode;

    void create_robot(robot_id_t id, size_t pos_x, size_t pos_y, Direction direction, std::string script_file);
    void update_robots();
    void print_battlefield();
    void refresh_battlefield();
    size_t teams_alive();

public:
    BattleController(size_t number_of_teams, GAME_MODE game_mode);
    void setup_robots();
    void setup_battlefield();
    void simulate_battle();
};

#endif