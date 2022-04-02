add_library(chronicle-common
    "log.cpp"
    "log.h"
    "platform_detect.h"
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
)

if(CMAKE_BUILD_TYPE MATCHES DEBUG)
    target_compile_definitions(chronicle-common PUBLIC CHR_MINIMUM_LOG_LEVEL=0)
else()
    target_compile_definitions(chronicle-common
        PUBLIC
            CHR_MINIMUM_LOG_LEVEL=2
            NDEBUG
    )
endif()

if(WIN32)
    target_compile_definitions(chronicle-common PUBLIC CHR_PLATFORM_WINDOWS)
elseif(APPLE)
    target_compile_definitions(chronicle-common PUBLIC CHR_PLATFORM_MACOS)
elseif(UNIX)
    target_compile_definitions(chronicle-common PUBLIC CHR_PLATFORM_LINUX)
endif()
