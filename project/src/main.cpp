#include "battle_controller.hpp"
#include <plog/Appenders/ColorConsoleAppender.h>
#include <plog/Formatters/TxtFormatter.h>
#include <plog/Init.h>

int main(int argc, char** argv)
{
    static plog::ColorConsoleAppender<plog::TxtFormatter> consoleAppender;
    plog::init(plog::verbose, &consoleAppender);
    // todo improve logging to show only needed info

    BattleController battle;
    battle.setup_battlefield();
    battle.setup_robots();
    battle.simulate_battle();
    return 0;
}
