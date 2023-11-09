cmake_minimum_required(VERSION 3.8)

project(homework2)

add_executable(homework2
    hello_world.cpp
    example.cpp
    example.h
    move_me_out.cpp
    move_me_out.h
)

set_target_properties(homework2 PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

if(MSVC)
    target_compile_options(homework2 PUBLIC /W4 /WX)
else()
    target_compile_options(homework2 PUBLIC -Wall -Wextra -Werror -pedantic)
endif()