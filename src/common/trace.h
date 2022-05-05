// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#ifndef CHR_COMMON_TRACE_H_
#define CHR_COMMON_TRACE_H_

#include <Tracy.hpp>

#if defined(TRACY_ENABLE)

#define CHR_ZONE_NAMED(varname, active)                                      \
  static constexpr tracy::SourceLocationData TracyConcat(                    \
      __tracy_source_location, __LINE__){nullptr, __FUNCTION__, __FILE__,    \
                                         (uint32_t)__LINE__, 0};             \
  tracy::ScopedZone varname(&TracyConcat(__tracy_source_location, __LINE__), \
                            active)

#define CHR_ZONE_NAMED_COLOR(varname, color, active)                         \
  static constexpr tracy::SourceLocationData TracyConcat(                    \
      __tracy_source_location, __LINE__){nullptr, __FUNCTION__, __FILE__,    \
                                         (uint32_t)__LINE__, color};         \
  tracy::ScopedZone varname(&TracyConcat(__tracy_source_location, __LINE__), \
                            active)

#define CHR_ZONE_SCOPED() ZoneScoped
#define CHR_ZONE_SCOPED_COLOR(color) ZoneScopedC(color)

inline void* operator new(std::size_t count) {
  auto ptr = malloc(count);
  TracyAlloc(ptr, count);
  return ptr;
}
inline void operator delete(void* ptr) noexcept {
  TracyFree(ptr);
  free(ptr);
}

#else

#define CHR_ZONE_SCOPED()
#define CHR_ZONE_SCOPED_COLOR(color)

#endif

#endif  // CHR_COMMON_TRACE_H_