#include "battle_controller.hpp"
#include <plog/Appenders/ColorConsoleAppender.h>
#include <plog/Formatters/TxtFormatter.h>
#include <plog/Init.h>

int main(int argc, char** argv)
{
    static plog::ColorConsoleAppender<plog::TxtFormatter> consoleAppender;
    plog::init(plog::verbose, &consoleAppender);

    // todo take option for number of teams
    // and option for gamemode
    // then take list of script files

    BattleController battle(3, GAME_MODE::DEATHMATCH);
    battle.setup_battlefield();
    battle.setup_robots();
    battle.simulate_battle();
    return 0;
}
