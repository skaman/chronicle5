#pragma once

namespace chr {

enum class platform_type { windows, macos, linux };

#if defined(CHR_PLATFORM_WINDOWS)
constexpr platform_type current_platform_type = platform_type::windows;
#elif defined(CHR_PLATFORM_MACOS)
constexpr platform_type current_platform_type = platform_type::macos;
#elif defined(CHR_PLATFORM_LINUX)
constexpr platform_type current_platform_type = platform_type::linux;
#else
#error "Unknown platform"
#endif

} // namespace chr