set(MathFunctions_Module_NAME MathFunctions)

add_library(${MathFunctions_Module_NAME} MathFunctions.cxx mysqrt.cxx)

target_include_directories(
    ${MathFunctions_Module_NAME}
    INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${MathFunctions_Module_NAME} tutorial_compiler_flags)

# install MathFunctions library to lib dir
set(installable_libs ${MathFunctions_Module_NAME} tutorial_compiler_flags)
install(TARGETS ${installable_libs} DESTINATION lib)

# install MathFunctions header to include dir
install(FILES MathFunctions.h DESTINATION include)
