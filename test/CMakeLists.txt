# Setup tests:
# https://www.jetbrains.com/help/clion/unit-testing-tutorial.html#adding-framework

project(tests)

message("   Building tests folder")

set(CMAKE_CXX_FLAGS "-O0 -g -Wall -Wextra --coverage")

add_subdirectory(lib/googletest)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(INCLUDE_TESTS
        unittests/TestWindow.cpp
        unittests/TestWindow.h
        unittests/TestUIElement.cpp
        unittests/TestUIElement.h
        unittests/TestGameObject.cpp
        unittests/TestGameObject.h
        unittests/TestButton.cpp
        unittests/TestButton.h
        )

add_executable(run_tests
        ${INCLUDE_TESTS}
        )

target_link_libraries(run_tests PIXELGUI_lib)

target_link_libraries(run_tests gtest_main)

add_test(NAME TEST COMMAND run_tests)
