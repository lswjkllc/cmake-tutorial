cmake_minimum_required(VERSION 3.10)                       # current camke version: 3.25.2

# project(Tutorial)
project(Tutorial VERSION 1.0)                              # add project version

# Specifying C++ standards
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)

configure_file(TutorialConfig.h.in TutorialConfig.h)       # configured file

add_executable(${PROJECT_NAME} tutorial.cxx)
message(STATUS "===> Project Binary Dir: ${PROJECT_BINARY_DIR}")
target_include_directories(                                # add include path for target
    ${PROJECT_NAME}
    PUBLIC
    ${PROJECT_BINARY_DIR})
