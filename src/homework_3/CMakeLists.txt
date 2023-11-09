cmake_minimum_required(VERSION 3.8)

project(homework3)

add_executable(homework3
    main.cpp    
)

set_target_properties(homework3 PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

if(MSVC)
    target_compile_options(homework3 PUBLIC /W4 /WX)
else()
    target_compile_options(homework3 PUBLIC -Wall -Wextra -Werror -pedantic)
endif()