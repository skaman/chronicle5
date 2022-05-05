add_library(chronicle-storage
    "entry.h"
    "file.h"
    "storage.cc"
    "storage.h"
    "filesystem/filesystem_entry.cc"
    "filesystem/filesystem_entry.h"
    "filesystem/filesystem_file.cc"
    "filesystem/filesystem_file.h"
    "filesystem/filesystem_storage.cc"
    "filesystem/filesystem_storage.h"
)

add_library(chronicle::storage ALIAS chronicle-storage)

set_property(TARGET chronicle-storage PROPERTY CXX_STANDARD 20)

target_include_directories(chronicle-storage
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
    INTERFACE
        ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(chronicle-storage
    PUBLIC
        chronicle::common
)
