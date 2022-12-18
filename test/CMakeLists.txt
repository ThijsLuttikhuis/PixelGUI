# Setup tests:
# https://www.jetbrains.com/help/clion/unit-testing-tutorial.html#adding-framework

project(tests)

add_subdirectory(lib/googletest)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(INCLUDE_TESTS
        unittests/TestWindow.cpp
        unittests/TestWindow.h)

add_executable(run_tests
        ${INCLUDE_TESTS}
        )

target_link_libraries(run_tests PIXELGUI_lib)

target_link_libraries(run_tests gtest gtest_main)

