#include "log.h"

namespace chr::log {

auto set_level(level lvl) -> void { spdlog::set_level(level_to_spdlog_(lvl)); }

} // namespace chr::log