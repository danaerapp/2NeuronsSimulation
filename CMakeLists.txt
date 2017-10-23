cmake_minimum_required (VERSION 2.6)
project(Neuron)
set(CMAKE_CXX_FLAGS "-O3 -W -Wall -pedantic -std=c++11")

enable_testing()
add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable (neurone Neuron_Main.cpp Neuron.cpp Network.cpp)
add_executable (NeuronUnitTest UnitTest_Main.cpp Neuron.cpp)

target_link_libraries(NeuronUnitTest gtest gtest_main)
add_test(NeuronUnitTest NeuronUnitTest)
