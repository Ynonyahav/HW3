cmake_minimum_required(VERSION 3.25)
project(HW3)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(HW3
        HealthPoints.cpp
        HealthPoints.h
        HealthPointsExampleTest.cpp
        Queue.h
        TestMain.cpp
        TestUtils.cpp
        TestUtils.h QueueExampleTest.cpp)
