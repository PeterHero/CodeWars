#include "battle_controller.hpp"
#include <filesystem>
#include <plog/Appenders/ColorConsoleAppender.h>
#include <plog/Formatters/TxtFormatter.h>
#include <plog/Init.h>
#include <string>

/**
 * @brief Prints program help
 *
 */
void print_help()
{
    std::cout << std::endl
              << "Usage: code_wars [OPTION]... [SCRIPT FILES]..." << std::endl
              << "Code wars simulates fight of robots run by scripts" << std::endl
              << std::endl
              << "Options:" << std::endl
              << "-t [number]     set number of teams/robots (default is 10)" << std::endl
              << "-m [mode]       set gamemode to one of [deathmatch/teams/capture] (default is deathmatch)" << std::endl
              << "-s [number]     set game seed (default is random)" << std::endl
              << "-h              print help" << std::endl;
}

int main(int argc, char** argv)
{
    static plog::ColorConsoleAppender<plog::TxtFormatter> consoleAppender;
    plog::init(plog::verbose, &consoleAppender);

    int teams = 10;
    GAME_MODE game_mode = GAME_MODE::DEATHMATCH;
    std::vector<std::string> scripts;
    std::optional<int> seed = std::nullopt;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-t") {
            if (i == argc - 1) {
                std::cout << "Missing argument for -t" << std::endl;
                print_help();
                return 1;
            }
            try {
                teams = std::stoi(argv[++i]);
            } catch (std::exception&) {
                std::cout << "Invalid argument for -t, expected a number" << std::endl;
                print_help();
                return 1;
            }
        } else if (arg == "-m") {
            if (i == argc - 1) {
                std::cout << "Missing argument for -m" << std::endl;
                print_help();
                return 1;
            }
            std::string mode(argv[++i]);
            if (mode == "deathmatch") {
                game_mode = GAME_MODE::DEATHMATCH;
            } else if (mode == "teams") {
                game_mode = GAME_MODE::TEAM_DM;
            } else if (mode == "capture") {
                game_mode = GAME_MODE::POINTS;
            } else {
                std::cout << "Invalid game mode for -m" << std::endl;
                print_help();
                return 1;
            }
        } else if (arg == "-s") {
            if (i == argc - 1) {
                std::cout << "Missing argument for -s" << std::endl;
                print_help();
                return 1;
            }
            try {
                seed = std::stoi(argv[++i]);
            } catch (std::exception&) {
                std::cout << "Invalid argument for -s, expected a number" << std::endl;
                print_help();
                return 1;
            }
        } else if (arg == "-h") {
            print_help();
            return 0;
        } else {
            if (std::filesystem::exists(arg)) {
                scripts.push_back(arg);
            } else {
                std::cout << "Not a file: " << arg << std::endl;
            }
        }
    }

    if (scripts.size() == 0) {
        std::cout << "At least 1 script is needed" << std::endl;
        print_help();
        return 1;
    }

    size_t team_size = (game_mode == GAME_MODE::TEAM_DM) ? 3 : 1;

    BattleController battle(game_mode, seed);

    battle.setup_battlefield();
    battle.setup_robots(scripts, teams, team_size);
    battle.simulate_battle();

    return 0;
}
