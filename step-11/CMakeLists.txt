# current camke version: 3.25.2
# generator expressions required cmake minimum verion is 3.15
cmake_minimum_required(VERSION 3.15)

# project(Tutorial)
project(Tutorial VERSION 1.0)                                 # add project version

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
    "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>>"
    "$<${msvc_cxx}:$<BUILD_INTERFACE:-W3>>"
)
# target_compile_options(
#     tutorial_compiler_flags
#     INTERFACE
#     "$<${gcc_like_cxx}:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>"
#     "$<${msvc_cxx}:-W3>"
# )

# Control where the static and shared libraries are built so that on windows
# we don't need to tinker with the path to run the executable
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

# Rebuild configured file
configure_file(TutorialConfig.h.in TutorialConfig.h)

# add subdirectory for using custom functions -----------------------------------------------------------
## -------- 方式一 --------
add_subdirectory(MathFunctions)

## -------- 方式二 --------
# if (USE_MYMATH)
#     add_subdirectory(MathFunctions)                               
#     list(APPEND EXTRA_LIBS MathFunctions)
#     # list(APPEND EXTRA_INCLUDES ${PROJECT_SOURCE_DIR}/MathFunctions)
# endif()

# Add executable
add_executable(${PROJECT_NAME} tutorial.cxx)
target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
    MathFunctions
    tutorial_compiler_flags
)
target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    ${PROJECT_BINARY_DIR}
)

# install -----------------------------------------------------------------------------------------------
## install Tutorial target to bin dir
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
## install Tutorial header to include dir
install(FILES "${PROJECT_BINARY_DIR}/TutorialConfig.h" DESTINATION include)

# enable test or test dashboard, Choose one -------------------------------------------------------------
# enable_testing()
include(CTest)

add_test(NAME Runs COMMAND ${PROJECT_NAME} 25)
set_tests_properties(Runs PROPERTIES PASS_REGULAR_EXPRESSION "25 is 5")

add_test(NAME Usage COMMAND ${PROJECT_NAME})
set_tests_properties(Usage PROPERTIES PASS_REGULAR_EXPRESSION "Usage:.*number")

add_test(NAME StandardUse COMMAND ${PROJECT_NAME} 4)
set_tests_properties(StandardUse PROPERTIES PASS_REGULAR_EXPRESSION "4 is 2")

# test function: do_test
function(do_test target arg result)
  add_test(NAME Comp${arg} COMMAND ${target} ${arg})
  set_tests_properties(Comp${arg} PROPERTIES PASS_REGULAR_EXPRESSION ${result})
endfunction()
# do a bunch of result based tests
do_test(${PROJECT_NAME} 4 "4 is 2")
do_test(${PROJECT_NAME} 9 "9 is 3")
do_test(${PROJECT_NAME} 5 "5 is 2.236")
do_test(${PROJECT_NAME} 7 "7 is 2.645")
do_test(${PROJECT_NAME} 25 "25 is 5")
do_test(${PROJECT_NAME} -25 "-25 is (-nan|nan|0)")
do_test(${PROJECT_NAME} 0.0001 "0.0001 is 0.01")

# package current project -------------------------------------------------------------------------------
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${Tutorial_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${Tutorial_VERSION_MINOR}")
set(CPACK_SOURCE_GENERATOR "TGZ")
include(CPack)

# export current project --------------------------------------------------------------------------------
install(
    EXPORT MathFunctionsTargets
    FILE MathFunctionsTargets.cmake
    DESTINATION lib/cmake/MathFunctions
)

include(CMakePackageConfigHelpers)
# generate the config file that includes the exports
configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/MathFunctionsConfig.cmake"
    INSTALL_DESTINATION "lib/cmake/example"
    NO_SET_AND_CHECK_MACRO
    NO_CHECK_REQUIRED_COMPONENTS_MACRO
)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/MathFunctionsConfigVersion.cmake"
    VERSION "${Tutorial_VERSION_MAJOR}.${Tutorial_VERSION_MINOR}"
    COMPATIBILITY AnyNewerVersion
)

install(
    FILES
    ${CMAKE_CURRENT_BINARY_DIR}/MathFunctionsConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/MathFunctionsConfigVersion.cmake
    DESTINATION lib/cmake/MathFunctions
)

export(
    EXPORT MathFunctionsTargets
    FILE "${CMAKE_CURRENT_BINARY_DIR}/MathFunctionsTargets.cmake"
)