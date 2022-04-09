#pragma once

#include <iostream>

#include "log.h"

namespace chr {

struct assert_failure {
  template <typename Fun> explicit assert_failure(Fun fun) {
    fun();
    std::quick_exit(EXIT_FAILURE);
  }
};

constexpr void assert_if_not(bool condition, const std::string &message) {
  if constexpr (CHR_ENABLE_ASSERTS) {
    if (!condition) {
      log::critical("{}", message);
      throw assert_failure([] { assert(false); });
    }
  }
}

} // namespace chr