#pragma once

#include <iostream>
#include <spdlog/spdlog.h>

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
} // namespace std
#endif

#ifndef CHR_MINIMUM_LOG_LEVEL
#define CHR_MINIMUM_LOG_LEVEL 0
#endif

namespace chr::log {

enum class level : int {
  trace = 0,
  debug = 1,
  info = 2,
  warn = 3,
  err = 4,
  critical = 5,
  off = 6
};

constexpr auto level_to_spdlog_(level lvl) noexcept
    -> spdlog::level::level_enum {
  switch (lvl) {
  case chr::log::level::trace:
    return spdlog::level::trace;
  case chr::log::level::debug:
    return spdlog::level::debug;
  case chr::log::level::info:
    return spdlog::level::info;
  case chr::log::level::warn:
    return spdlog::level::warn;
  case chr::log::level::err:
    return spdlog::level::err;
  case chr::log::level::critical:
    return spdlog::level::critical;
  default:
    return spdlog::level::off;
    break;
  }
}

template <level lvl, typename... Args>
constexpr auto log_(const std::source_location &location,
                    spdlog::format_string_t<Args...> format, Args &&...args)
    -> void {
  if constexpr (static_cast<int>(lvl) >= CHR_MINIMUM_LOG_LEVEL) {
    spdlog::default_logger_raw()->log(
        spdlog::source_loc{location.file_name(),
                           static_cast<int>(location.line()),
                           location.function_name()},
        level_to_spdlog_(lvl), format, std::forward<Args>(args)...);
  }
}

auto set_level(level lvl) -> void;

template <typename... Args> struct trace {
  constexpr trace(
      spdlog::format_string_t<Args...> format, Args &&...args,
      const std::source_location &loc = std::source_location::current()) {
    log_<level::trace>(loc, format, static_cast<Args &&>(args)...);
  }
};

template <typename... Args> struct debug {
  constexpr debug(
      spdlog::format_string_t<Args...> format, Args &&...args,
      const std::source_location &loc = std::source_location::current()) {
    log_<level::debug>(loc, format, static_cast<Args &&>(args)...);
  }
};

template <typename... Args> struct info {
  constexpr info(
      spdlog::format_string_t<Args...> format, Args &&...args,
      const std::source_location &loc = std::source_location::current()) {
    log_<level::info>(loc, format, static_cast<Args &&>(args)...);
  }
};

template <typename... Args> struct warn {
  constexpr warn(
      spdlog::format_string_t<Args...> format, Args &&...args,
      const std::source_location &loc = std::source_location::current()) {
    log_<level::warn>(loc, format, static_cast<Args &&>(args)...);
  }
};

template <typename... Args> struct err {
  constexpr err(
      spdlog::format_string_t<Args...> format, Args &&...args,
      const std::source_location &loc = std::source_location::current()) {
    log_<level::err>(loc, format, static_cast<Args &&>(args)...);
  }
};

template <typename... Args> struct critical {
  constexpr critical(
      spdlog::format_string_t<Args...> format, Args &&...args,
      const std::source_location &loc = std::source_location::current()) {
    log_<level::critical>(loc, format, static_cast<Args &&>(args)...);
  }
};

template <typename... Args>
trace(spdlog::format_string_t<Args...> &&, Args &&...) -> trace<Args...>;

template <typename... Args>
debug(spdlog::format_string_t<Args...> &&, Args &&...) -> debug<Args...>;

template <typename... Args>
info(spdlog::format_string_t<Args...> &&, Args &&...) -> info<Args...>;

template <typename... Args>
warn(spdlog::format_string_t<Args...> &&, Args &&...) -> warn<Args...>;

template <typename... Args>
err(spdlog::format_string_t<Args...> &&, Args &&...) -> err<Args...>;

template <typename... Args>
critical(spdlog::format_string_t<Args...> &&, Args &&...) -> critical<Args...>;

} // namespace chr::log