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

    GAME_MODE _game_mode;

    void create_robot(robot_id_t id, size_t team_id, Direction direction, std::string script_file);
    void create_object(std::unique_ptr<FieldObject> object);
    template <typename T>
    void create_objects(size_t count)
    {
        for (size_t i = 0; i < count; ++i)
            create_object(std::make_unique<T>());
    }
    void update_robots();
    void print_battlefield();
    void refresh_battlefield();
    size_t teams_alive();
    void get_free_field(size_t& pos_x, size_t& pos_y);

public:
    BattleController(GAME_MODE game_mode, std::optional<int> seed);
    void setup_robots(std::vector<std::string>& scripts, size_t number_of_teams, size_t robots_in_team);
    void setup_battlefield();
    void simulate_battle();
};

#endif