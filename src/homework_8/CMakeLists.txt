cmake_minimum_required(VERSION 3.8)

project(homework_8)

add_executable(topk topk_words.cpp)
set_target_properties(topk PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

if(MSVC)
    target_compile_options(topk PUBLIC /W4 /WX)
else()
    target_compile_options(topk PUBLIC -Wall -Wextra -Werror -pedantic)
endif()