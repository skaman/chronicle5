add_library(chronicle-common
    INTERFACE
        "log.hpp"
)

add_library(chronicle::common ALIAS chronicle-common)

set_property(TARGET chronicle-common PROPERTY CXX_STANDARD 20)

target_include_directories(chronicle-common
    INTERFACE
        ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(chronicle-common
    INTERFACE
        spdlog
)

#add_definitions(-DCHR_LOG_ACTIVE_LEVEL=0)
