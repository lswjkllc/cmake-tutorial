# file(GLOB MathFunctions_Source_FILES "...")
add_library(MathFunctions MathFunctions.cxx mysqrt.cxx)

target_include_directories(
    MathFunctions
    INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR})
