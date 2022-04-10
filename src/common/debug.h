#pragma once

#include <iostream>

#include "log.h"

namespace chr::debug {

struct assert_failure {
  template <typename Fun> explicit assert_failure(Fun fun) {
    fun();
    std::quick_exit(EXIT_FAILURE);
  }
};

constexpr auto assert_true(bool condition, const std::string &message)
    -> void {
  if constexpr (CHR_ENABLE_ASSERTS) {
    if (!condition) {
      log::critical("{}", message);
      throw assert_failure([] { assert(false); });
    }
  }
}

} // namespace chr