add_executable(example1 "example_app.cpp" "example_app.h")

set_property(TARGET example1 PROPERTY CXX_STANDARD 20)

target_link_libraries(example1 PRIVATE
    chronicle::common
    chronicle::platform
)