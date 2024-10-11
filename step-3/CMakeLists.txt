cmake_minimum_required(VERSION 3.10)                          # current camke version: 3.25.2

# project(Tutorial)
project(Tutorial VERSION 1.0)                                 # add project version

# Setting options for compiling modules
option(USE_MYMATH "Use tutorial provided math implementation" ON)

# Specifying C++ standards
# set(CMAKE_CXX_STANDARD 11)
# set(CMAKE_CXX_STANDARD_REQUIRED true)

# Add executable
add_executable(${PROJECT_NAME} tutorial.cxx)

# Rebuild configured file
configure_file(TutorialConfig.h.in TutorialConfig.h)
target_include_directories(                                   # add include path for target
    ${PROJECT_NAME}
    PUBLIC
    ${PROJECT_BINARY_DIR}
)

# add subdirectory for using custom functions -----------------------------------------------------------
## -------- 方式一 --------
# add_subdirectory(MathFunctions)
# target_link_libraries(
#     ${PROJECT_NAME}
#     PUBLIC
#     MathFunctions
# )
# target_include_directories(                                   # add include path for target
#     ${PROJECT_NAME}
#     PUBLIC
#     ${PROJECT_BINARY_DIR}
#     ${PROJECT_SOURCE_DIR}/MathFunctions
# )

## -------- 方式二 --------
if (USE_MYMATH)
    add_subdirectory(MathFunctions)                               
    list(APPEND EXTRA_LIBS MathFunctions)
    # list(APPEND EXTRA_INCLUDES ${PROJECT_SOURCE_DIR}/MathFunctions)
endif()
target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
    ${EXTRA_LIBS}
)
target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    ${PROJECT_BINARY_DIR}
    # ${EXTRA_INCLUDES}
)
