#pragma once

#ifdef __cpp_lib_source_location
#include <source_location>
#else
// in case of there's no support for source location,
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

#include <spdlog/spdlog.h>

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

constexpr auto level_to_spdlog_(level lvl) -> spdlog::level::level_enum {
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
  case chr::log::level::off:
  default:
    return spdlog::level::off;
    break;
  }
}

template <level lvl, typename... Args>
constexpr auto log_(const std::source_location &location,
                    spdlog::format_string_t<Args...> fmt, Args &&...args)
    -> void {
  if constexpr (static_cast<int>(lvl) >= CHR_MINIMUM_LOG_LEVEL) {
    spdlog::default_logger_raw()->log(
        spdlog::source_loc{location.file_name(),
                           static_cast<int>(location.line()),
                           location.function_name()},
        level_to_spdlog_(lvl), fmt, std::forward<Args>(args)...);
  }
}

auto set_level(level lvl) -> void { spdlog::set_level(level_to_spdlog_(lvl)); }

template <typename... P> struct trace {
  constexpr trace(
      spdlog::format_string_t<P...> &&format, P &&...params,
      const std::source_location &loc = std::source_location::current()) {
    log_<level::trace>(loc, format, std::forward<P>(params)...);
  }
};

template <typename... P> struct debug {
  constexpr debug(
      spdlog::format_string_t<P...> &&format, P &&...params,
      const std::source_location &loc = std::source_location::current()) {
    log_<level::debug>(loc, format, std::forward<P>(params)...);
  }
};

template <typename... P> struct info {
  constexpr info(
      spdlog::format_string_t<P...> &&format, P &&...params,
      const std::source_location &loc = std::source_location::current()) {
    log_<level::info>(loc, format, std::forward<P>(params)...);
  }
};

template <typename... P> struct warn {
  constexpr warn(
      spdlog::format_string_t<P...> &&format, P &&...params,
      const std::source_location &loc = std::source_location::current()) {
    log_<level::warn>(loc, format, std::forward<P>(params)...);
  }
};

template <typename... P> struct err {
  constexpr err(
      spdlog::format_string_t<P...> &&format, P &&...params,
      const std::source_location &loc = std::source_location::current()) {
    log_<level::err>(loc, format, std::forward<P>(params)...);
  }
};

template <typename... P> struct critical {
  constexpr critical(
      spdlog::format_string_t<P...> &&format, P &&...params,
      const std::source_location &loc = std::source_location::current()) {
    log_<level::critical>(loc, format, std::forward<P>(params)...);
  }
};

template <typename... P>
trace(spdlog::format_string_t<P...> &&, P &&...) -> trace<P...>;

template <typename... P>
debug(spdlog::format_string_t<P...> &&, P &&...) -> debug<P...>;

template <typename... P>
info(spdlog::format_string_t<P...> &&, P &&...) -> info<P...>;

template <typename... P>
warn(spdlog::format_string_t<P...> &&, P &&...) -> warn<P...>;

template <typename... P>
err(spdlog::format_string_t<P...> &&, P &&...) -> err<P...>;

template <typename... P>
critical(spdlog::format_string_t<P...> &&, P &&...) -> critical<P...>;

} // namespace chr::log