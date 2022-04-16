find_package(Vulkan REQUIRED)

add_library(chronicle-renderer
    "common.h"
    "device.h"
    "device.cc"
    "instance.cc"
    "instance.h"
    "pch.h"
    "platform.h"
    "platform.cc"
    "surface.cc"
    "surface.h"
    "vulkan/vulkan_device.cc"
    "vulkan/vulkan_device.h"
    "vulkan/vulkan_instance.cc"
    "vulkan/vulkan_instance.h"
    "vulkan/vulkan_pch.h"
    "vulkan/vulkan_surface.cc"
    "vulkan/vulkan_surface.h"
)

add_library(chronicle::renderer ALIAS chronicle-renderer)

set_property(TARGET chronicle-renderer PROPERTY CXX_STANDARD 20)

target_include_directories(chronicle-renderer
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}"
    INTERFACE
        "${CMAKE_SOURCE_DIR}/include"
)

target_precompile_headers(chronicle-renderer
    PRIVATE
        "pch.h"
        "vulkan/vulkan_pch.h"
)

target_link_libraries(chronicle-renderer
    PUBLIC
        EnTT::EnTT
        Vulkan::Headers
        Vulkan::Vulkan
        chronicle::common
)
