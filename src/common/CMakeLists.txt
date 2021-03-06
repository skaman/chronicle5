add_library(chronicle-common
    "debug.h"
    "log.cc"
    "log.h"
    "trace.h"
    "utils.h"
)

add_library(chronicle::common ALIAS chronicle-common)

set_property(TARGET chronicle-common PROPERTY CXX_STANDARD 20)

target_include_directories(chronicle-common
    INTERFACE
        ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(chronicle-common
    PUBLIC
        spdlog
        EnTT::EnTT
        Tracy::TracyClient
)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    target_compile_definitions(chronicle-common
        PUBLIC
            CHR_MINIMUM_LOG_LEVEL=0
            CHR_ENABLE_ASSERTS=1
    )
else()
    target_compile_definitions(chronicle-common
        PUBLIC
            CHR_MINIMUM_LOG_LEVEL=2
            CHR_ENABLE_ASSERTS=0
    )
endif()

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(chronicle-common
        PUBLIC
            -Wno-c++17-extensions
    )
endif()

if(WIN32)
    target_compile_definitions(chronicle-common PUBLIC CHR_PLATFORM_WINDOWS)
elseif(APPLE)
    target_compile_definitions(chronicle-common PUBLIC CHR_PLATFORM_MACOS)
elseif(UNIX)
    target_compile_definitions(chronicle-common PUBLIC CHR_PLATFORM_LINUX)
endif()
