// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#ifndef CHR_COMMON_DEBUG_H_
#define CHR_COMMON_DEBUG_H_

#include <iostream>

#include "log.h"

namespace chr::debug {

struct AssertFailure {
  template <typename Fun>
  explicit AssertFailure(Fun fun) {
    fun();
    std::quick_exit(EXIT_FAILURE);
  }
};

constexpr auto Assert(bool condition, const std::string &message) -> void {
  if constexpr (CHR_ENABLE_ASSERTS) {
    if (!condition) {
      log::Critical("{}", message);
      throw AssertFailure([] { assert(false); });
    }
  }
}

}  // namespace chr::debug

#endif  // CHR_COMMON_DEBUG_H_