#include <iostream>

#include <chronicle/common.h>

auto main() -> int {
  chr::log::set_level(chr::log::level::trace);

  chr::log::trace("Hello world");
  chr::log::debug("Hello world");
  chr::log::debug("Hello world {}", "CIAO");
  chr::log::debug("Hello world");
  chr::log::info("Hello world");
  chr::log::warn("Hello world");
  chr::log::err("Hello world");
  chr::log::critical("Hello world");
  return EXIT_SUCCESS;
}