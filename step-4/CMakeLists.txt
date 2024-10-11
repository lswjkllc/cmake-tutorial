# current camke version: 3.25.2
# generator expressions required cmake minimum verion is 3.15
cmake_minimum_required(VERSION 3.15)

# project(Tutorial)
project(Tutorial VERSION 1.0)                                 # add project version

# Setting options for compiling modules
option(USE_MYMATH "Use tutorial provided math implementation" ON)

# Specifying C++ standards ------------------------------------------------------------------------------
## -------- 方式一 --------
# set(CMAKE_CXX_STANDARD 11)
# set(CMAKE_CXX_STANDARD_REQUIRED true)

## -------- 方式二 --------
add_library(tutorial_compiler_flags INTERFACE)
target_compile_features(tutorial_compiler_flags INTERFACE cxx_std_11)
### add generator expressions 
set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")
target_compile_options(
    tutorial_compiler_flags
    INTERFACE
    "$<${gcc_like_cxx}:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>"
    "$<${msvc_cxx}:-W3>"
)
# target_compile_options(
#     tutorial_compiler_flags
#     INTERFACE
#     "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>>"
#     "$<${msvc_cxx}:$<BUILD_INTERFACE:-W3>>"
# )

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
