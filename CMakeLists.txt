cmake_minimum_required(VERSION 3.0)

project(Gtest)

enable_testing() 

add_subdirectory(googletest)

include_directories(googletest/googlemock/include)
include_directories(googletest/googletest/include)

add_executable(runUnitTest unitTest.cpp)

target_link_libraries(runUnitTest gtest gtest_main)
target_link_libraries(runUnitTest gmock gmock_main)

include(GoogleTest)
