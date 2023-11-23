cmake_minimum_required(VERSION 3.8)

project(homework_6)

add_executable(containers main.cpp)
set_target_properties(containers PROPERTIES
                                 CXX_STANDARD 17
                                 CXX_STANDARD_REQUIRED ON)

if(MSVC)
    target_compile_options(containers PUBLIC /W4 /WX)
else()
    target_compile_options(containers PUBLIC -Wall -Wextra -Werror -pedantic)
endif()