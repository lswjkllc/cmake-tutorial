
add_executable(MakeTable MakeTable.cxx)
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/Table.h
    COMMAND MakeTable ${CMAKE_CURRENT_BINARY_DIR}/Table.h
    DEPENDS MakeTable
)

set(MathFunctions_Module_NAME MathFunctions)

add_library(
  ${MathFunctions_Module_NAME}
  MathFunctions.cxx mysqrt.cxx ${CMAKE_CURRENT_BINARY_DIR}/Table.h)

target_include_directories(
    ${MathFunctions_Module_NAME}
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE   ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(${MathFunctions_Module_NAME} tutorial_compiler_flags)

# install MathFunctions library to lib dir
set(installable_libs ${MathFunctions_Module_NAME} tutorial_compiler_flags)
install(TARGETS ${installable_libs} DESTINATION lib)

# install MathFunctions header to include dir
install(FILES MathFunctions.h DESTINATION include)
