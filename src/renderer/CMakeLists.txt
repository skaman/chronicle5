find_package(Vulkan REQUIRED)

add_library(chronicle-renderer
    "command_buffer.h"
    "command_pool.h"
    "common.h"
    "device.h"
    "enums.cc"
    "enums.h"
    "fence.h"
    "frame_buffer.h"
    "image_view.h"
    "instance.cc"
    "instance.h"
    "pch.h"
    "pipeline.h"
    "render_pass.h"
    "semaphore.h"
    "shader.h"
    "shader_compiler.cc"
    "shader_compiler.h"
    "surface.h"
    "swap_chain.h"
    "vulkan/vulkan_command_buffer.cc"
    "vulkan/vulkan_command_buffer.h"
    "vulkan/vulkan_command_pool.cc"
    "vulkan/vulkan_command_pool.h"
    "vulkan/vulkan_device.cc"
    "vulkan/vulkan_device.h"
    "vulkan/vulkan_fence.cc"
    "vulkan/vulkan_fence.h"
    "vulkan/vulkan_frame_buffer.cc"
    "vulkan/vulkan_frame_buffer.h"
    "vulkan/vulkan_image_view.cc"
    "vulkan/vulkan_image_view.h"
    "vulkan/vulkan_instance.cc"
    "vulkan/vulkan_instance.h"
    "vulkan/vulkan_pch.h"
    "vulkan/vulkan_pipeline.cc"
    "vulkan/vulkan_pipeline.h"
    "vulkan/vulkan_render_pass.cc"
    "vulkan/vulkan_render_pass.h"
    "vulkan/vulkan_semaphore.cc"
    "vulkan/vulkan_semaphore.h"
    "vulkan/vulkan_shader.cc"
    "vulkan/vulkan_shader.h"
    "vulkan/vulkan_surface.cc"
    "vulkan/vulkan_surface.h"
    "vulkan/vulkan_swap_chain.cc"
    "vulkan/vulkan_swap_chain.h"
    "vulkan/vulkan_utils.cc"
    "vulkan/vulkan_utils.h"
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
        glm::glm
        Vulkan::Headers
        Vulkan::Vulkan
        chronicle::common
        spirv-cross-core
        spirv-cross-glsl
        shaderc
)
