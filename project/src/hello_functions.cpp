#include "hello_functions.hpp"

#include <iostream>
#include <plog/Appenders/ColorConsoleAppender.h>
#include <plog/Formatters/TxtFormatter.h>
#include <plog/Init.h>
#include <plog/Log.h>

void say_hello() { std::cout << "Hello, World!" << std::endl; }
void lib_hello() {
  static plog::ColorConsoleAppender<plog::TxtFormatter> consoleAppender;
  plog::init(plog::verbose, &consoleAppender);

  // Log severity levels are printed in different colors.
  PLOG_VERBOSE << "This is a VERBOSE message";
  PLOG_DEBUG << "This is a DEBUG message";
  PLOG_INFO << "This is an INFO message";
  PLOG_WARNING << "This is a WARNING message";
  PLOG_ERROR << "This is an ERROR message";
  PLOG_FATAL << "This is a FATAL message";
}
