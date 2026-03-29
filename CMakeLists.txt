cmake_minimum_required(VERSION 4.2)
project(motors)

set(CMAKE_CXX_STANDARD 20)

add_library(motors STATIC include/NonCopyable.h
        include/DCMotor.h
        include/AbstractMotors.h
        include/AbstractDriver.h)
