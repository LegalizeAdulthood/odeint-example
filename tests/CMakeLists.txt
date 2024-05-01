include(GoogleTest)

find_package(GTest CONFIG REQUIRED)

add_executable("test-dynamical-system" test.cpp)
target_link_libraries("test-dynamical-system" PUBLIC GTest::gtest_main "dynamical-system")
target_folder("test-dynamical-system" "Tests")

gtest_discover_tests("test-dynamical-system")
