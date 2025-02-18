#include "hello_functions.hpp"

#include "battle_controller.hpp"
#include <iostream>

int main(int argc, char **argv) {
  try {
    say_hello();
    lib_hello();
  } catch (const std::exception &e) {
    std::cout << e.what() << std::endl;
  } catch (...) {
    std::cout << "Unknown exception." << std::endl;
  }

  BattleController battle;
  battle.print_battlefield();
  return 0; // return code 0 required for recodex success
}
