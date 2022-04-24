// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#ifndef CHR_COMMON_UTILS_H_
#define CHR_COMMON_UTILS_H_

#include <algorithm>

namespace chr::utils {

template <typename K, typename V>
constexpr auto InverseMap(std::unordered_map<K, V> &map)
    -> std::unordered_map<V, K> {
  std::unordered_map<V, K> inverse_map(map.size());
  std::ranges::for_each(map, [&inverse_map](const std::pair<K, V> &p) {
    inverse_map.insert(std::make_pair(p.second, p.first));
  });
  return inverse_map;
}

}  // namespace chr::utils

#endif  // CHR_COMMON_UTILS_H_