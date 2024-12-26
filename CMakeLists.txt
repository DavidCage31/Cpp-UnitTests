cmake_minimum_required(VERSION 3.0)

project(Gtest) #name of your project

enable_testing() #to  discover tests in test explorer 

add_subdirectory(googletest) # add googletest subdirectory

include_directories(googletest/googlemock/include)
include_directories(googletest/googletest/include) # this is so we can #include <gtest/gtest.h>

add_executable(runUnitTest unitTest.cpp) # add this executable

target_link_libraries(runUnitTest gtest gtest_main) # link google test to this executable
target_link_libraries(runUnitTest gmock gmock_main)

include(GoogleTest)
