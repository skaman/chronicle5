find_package(Vulkan REQUIRED)

add_library(chronicle-renderer
    "common.h"
    "device.h"
    "instance.cc"
    "instance.h"
    "pch.h"
    "shader.h"
    "shader_compiler.cc"
    "shader_compiler.h"
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
        shaderc
)
