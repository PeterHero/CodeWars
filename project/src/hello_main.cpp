// #include "battle_controller.hpp"
#include "interpret.hpp"
#include <plog/Appenders/ColorConsoleAppender.h>
#include <plog/Formatters/TxtFormatter.h>
#include <plog/Init.h>

int main(int argc, char **argv) {
  static plog::ColorConsoleAppender<plog::TxtFormatter> consoleAppender;
  plog::init(plog::verbose, &consoleAppender);
  // todo improve logging to show only needed info

  // BattleController battle;
  Interpret interpret("examples/test.rbsh");
  for (size_t i = 0; i < 4; ++i) {
    if (interpret.next_command().type == Command::Type::MOVE) {
      std::cout << "move_cmd_it_is" << std::endl;
    }
  }
  return 0;
}
