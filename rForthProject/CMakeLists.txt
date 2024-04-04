cmake_minimum_required(VERSION 3.5)

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.14.0
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(int_stack_demo
        int_stack_demo.c
)

add_executable(
        int_stack_tests
        int_stacks_tests.cc
        int_stack.c
)

target_link_libraries(
        int_stack_tests
        gtest
        gtest_main
)

include(GoogleTest)
gtest_discover_tests(int_stack_tests)

add_executable(MainForth main.c)
#add_executable(TokenForth token.c) #doesn't have a main method
add_executable(TestTokenForth TestToken.c)
add_executable(rForthInterpreter rLoop.c)