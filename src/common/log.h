// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#ifndef CHR_COMMON_LOG_H_
#define CHR_COMMON_LOG_H_

#include <spdlog/spdlog.h>

#include <Tracy.hpp>
#include <iostream>

#ifdef __cpp_lib_source_location
#include <source_location>
#else
// In case of there's no support for source location,
// for the moment just create a fake struct just to feed
// the method. The log will not have any information about
// the source location, but at least it will compile.
namespace std {
struct source_location {
  constexpr uint_least32_t line() const noexcept { return 0; }
  constexpr const char *file_name() const noexcept { return ""; }
  constexpr const char *function_name() const noexcept { return ""; }

  static constexpr source_location current() noexcept {
    source_location result{};
    return result;
  }
};
}  // namespace std
#endif

#ifndef CHR_MINIMUM_LOG_LEVEL
#define CHR_MINIMUM_LOG_LEVEL 0
#endif

namespace chr::log {

enum class Level : int {
  kTrace = 0,
  kDebug = 1,
  kInfo = 2,
  kWarn = 3,
  kErr = 4,
  kCritical = 5,
  kOff = 6
};

namespace internal {

constexpr auto LevelToSpdlog(Level level) noexcept
    -> spdlog::level::level_enum {
  switch (level) {
    case chr::log::Level::kTrace:
      return spdlog::level::trace;
    case chr::log::Level::kDebug:
      return spdlog::level::debug;
    case chr::log::Level::kInfo:
      return spdlog::level::info;
    case chr::log::Level::kWarn:
      return spdlog::level::warn;
    case chr::log::Level::kErr:
      return spdlog::level::err;
    case chr::log::Level::kCritical:
      return spdlog::level::critical;
    default:
      return spdlog::level::off;
      break;
  }
}

constexpr auto LevelToTracyColor(Level level) noexcept
    -> uint32_t {
  switch (level) {
    case chr::log::Level::kTrace:
      return tracy::Color::Gray;
    case chr::log::Level::kDebug:
      return tracy::Color::Gray;
    case chr::log::Level::kInfo:
      return tracy::Color::White;
    case chr::log::Level::kWarn:
      return tracy::Color::Yellow;
    case chr::log::Level::kErr:
      return tracy::Color::Red;
    case chr::log::Level::kCritical:
      return tracy::Color::Red;
    default:
      return tracy::Color::White;
      break;
  }
}

template <Level level, typename... Args>
constexpr auto Log(const std::source_location &location,
                   spdlog::format_string_t<Args...> format, Args &&...args)
    -> void {
  if constexpr (static_cast<int>(level) >= CHR_MINIMUM_LOG_LEVEL) {
    spdlog::default_logger_raw()->log(
        spdlog::source_loc{location.file_name(),
                           static_cast<int>(location.line()),
                           location.function_name()},
        LevelToSpdlog(level), format, std::forward<Args>(args)...);
#if defined(TRACY_ENABLE)
    std::string message = fmt::format(format, std::forward<Args>(args)...);
    TracyMessageC(message.c_str(), message.size(), LevelToTracyColor(level));
#endif
  }
}

}  // namespace internal

auto SetLevel(Level level) -> void;

template <typename... Args>
struct Trace {
  constexpr Trace(
      spdlog::format_string_t<Args...> format, Args &&...args,
      const std::source_location &loc = std::source_location::current()) {
    internal::Log<Level::kTrace>(loc, format, static_cast<Args &&>(args)...);
  }
};

template <typename... Args>
struct Debug {
  constexpr Debug(
      spdlog::format_string_t<Args...> format, Args &&...args,
      const std::source_location &loc = std::source_location::current()) {
    internal::Log<Level::kDebug>(loc, format, static_cast<Args &&>(args)...);
  }
};

template <typename... Args>
struct Info {
  constexpr Info(
      spdlog::format_string_t<Args...> format, Args &&...args,
      const std::source_location &loc = std::source_location::current()) {
    internal::Log<Level::kInfo>(loc, format, static_cast<Args &&>(args)...);
  }
};

template <typename... Args>
struct Warn {
  constexpr Warn(
      spdlog::format_string_t<Args...> format, Args &&...args,
      const std::source_location &loc = std::source_location::current()) {
    internal::Log<Level::kWarn>(loc, format, static_cast<Args &&>(args)...);
  }
};

template <typename... Args>
struct Err {
  constexpr Err(
      spdlog::format_string_t<Args...> format, Args &&...args,
      const std::source_location &loc = std::source_location::current()) {
    internal::Log<Level::kErr>(loc, format, static_cast<Args &&>(args)...);
  }
};

template <typename... Args>
struct Critical {
  constexpr Critical(
      spdlog::format_string_t<Args...> format, Args &&...args,
      const std::source_location &loc = std::source_location::current()) {
    internal::Log<Level::kCritical>(loc, format, static_cast<Args &&>(args)...);
  }
};

template <typename... Args>
Trace(spdlog::format_string_t<Args...> &&, Args &&...) -> Trace<Args...>;

template <typename... Args>
Debug(spdlog::format_string_t<Args...> &&, Args &&...) -> Debug<Args...>;

template <typename... Args>
Info(spdlog::format_string_t<Args...> &&, Args &&...) -> Info<Args...>;

template <typename... Args>
Warn(spdlog::format_string_t<Args...> &&, Args &&...) -> Warn<Args...>;

template <typename... Args>
Err(spdlog::format_string_t<Args...> &&, Args &&...) -> Err<Args...>;

template <typename... Args>
Critical(spdlog::format_string_t<Args...> &&, Args &&...) -> Critical<Args...>;

}  // namespace chr::log

#endif  // CHR_COMMON_LOG_H_