find_package(Vulkan REQUIRED)

add_library(chronicle-platform
    "events.h"
    "platform.h"
    "glfw/glfw_map.h"
    "glfw/glfw_map.cc"
    "glfw/glfw_platform.cc"
    "glfw/glfw_platform.h"
    "glfw/main.cc"
)

add_library(chronicle::platform ALIAS chronicle-platform)

set_property(TARGET chronicle-platform PROPERTY CXX_STANDARD 20)

target_include_directories(chronicle-platform
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
    INTERFACE
        ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(chronicle-platform
    PUBLIC
        glfw
        chronicle::common
        chronicle::renderer
)
