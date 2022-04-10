find_package(Vulkan REQUIRED)

add_library(chronicle-renderer
    "vulkan/vulkan_device.cpp"
    "vulkan/vulkan_device.h"
    "vulkan/vulkan_instance.cpp"
    "vulkan/vulkan_instance.h"
    "vulkan/vulkan_pch.h"
    "vulkan/vulkan_surface.cpp"
    "vulkan/vulkan_surface.h"
    "device.h"
    "device.cpp"
    "instance.cpp"
    "instance.h"
    "pch.h"
    "platform.h"
    "platform.cpp"
    "surface.cpp"
    "surface.h"
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
        glfw
        EnTT::EnTT
        Vulkan::Headers
        Vulkan::Vulkan
        chronicle::common
)
