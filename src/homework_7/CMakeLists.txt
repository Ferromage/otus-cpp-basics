cmake_minimum_required(VERSION 3.14)

project(homework_7)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(container_tests array_tests.cpp single_list_tests.cpp)
target_link_libraries(container_tests gtest gtest_main)

set_target_properties(container_tests PROPERTIES  CXX_STANDARD 17
                                        CXX_STANDARD_REQUIRED ON)

if(MSVC)
    target_compile_options(container_tests PUBLIC /W4 /WX)
else()
    target_compile_options(container_tests PUBLIC -Wall -Wextra -Werror -pedantic)
endif()