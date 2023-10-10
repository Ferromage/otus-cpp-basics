cmake_minimum_required(VERSION 3.8)

project(hello_world)

add_executable(hello 
    src/hello_world.cpp
    src/example.cpp
    src/example.h
    src/move_me_out.cpp
    src/move_me_out.h
)

set_target_properties(hello PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

if(MSVC)
    target_compile_options(hello PUBLIC /W4 /WX)
else()
    target_compile_options(hello PUBLIC -Wall -Wextra -Werror -pedantic)
endif()