cmake_minimum_required(VERSION 3.8)

project(homework1)

add_executable(homework1
    hello_world.cpp
    example.cpp
    example.h
    move_me_out.cpp
    move_me_out.h
)

set_target_properties(homework1 PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

if(MSVC)
    target_compile_options(homework1 PUBLIC /W4 /WX)
else()
    target_compile_options(homework1 PUBLIC -Wall -Wextra -Werror -pedantic)
endif()