add_executable(example1 "main.cpp")

set_property(TARGET example1 PROPERTY CXX_STANDARD 20)

target_link_libraries(example1 PRIVATE
    chronicle::common
)