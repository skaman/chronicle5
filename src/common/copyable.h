// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#ifndef CHR_COMMON_COPYABLE_H_
#define CHR_COMMON_COPYABLE_H_

namespace chr {

struct NonCopyable {
  NonCopyable() = default;
  NonCopyable(const NonCopyable &) = delete;
  NonCopyable &operator=(const NonCopyable &) = delete;
};

}  // namespace chr

#endif  // CHR_COMMON_COPYABLE_H_