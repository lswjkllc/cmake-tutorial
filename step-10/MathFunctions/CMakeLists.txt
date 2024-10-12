
set(MathFunctions_Module_NAME MathFunctions)

add_library(${MathFunctions_Module_NAME} MathFunctions.cxx)

target_include_directories(${MathFunctions_Module_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# should we use our own math functions
option(USE_MYMATH "Use tutorial provided math implementation" ON)
if (USE_MYMATH)
    target_compile_definitions(${MathFunctions_Module_NAME} PRIVATE "USE_MYMATH")

    # first we add the executable that generates the table
    add_executable(MakeTable MakeTable.cxx)
    target_link_libraries(MakeTable PRIVATE tutorial_compiler_flags)
    # add the command to generate the source code
    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/Table.h
        COMMAND MakeTable ${CMAKE_CURRENT_BINARY_DIR}/Table.h
        DEPENDS MakeTable
    )

    # library that just does sqrt
    add_library(SqrtLibrary STATIC mysqrt.cxx ${CMAKE_CURRENT_BINARY_DIR}/Table.h)
    # state that we depend on our binary dir to find Table.h
    target_include_directories(SqrtLibrary PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
    # state that SqrtLibrary need PIC when the default is shared libraries
    set_target_properties(SqrtLibrary PROPERTIES POSITION_INDEPENDENT_CODE ${BUILD_SHARED_LIBS})

    target_link_libraries(SqrtLibrary PUBLIC tutorial_compiler_flags)
    target_link_libraries(${MathFunctions_Module_NAME} PRIVATE SqrtLibrary)
endif()

target_link_libraries(${MathFunctions_Module_NAME} PUBLIC tutorial_compiler_flags)

# define the symbol stating we are using the declspec(dllexport) when building on windows
target_compile_definitions(${MathFunctions_Module_NAME} PRIVATE "EXPORTING_MYMATH")

# install libs
set(installable_libs ${MathFunctions_Module_NAME} tutorial_compiler_flags)
if(TARGET SqrtLibrary)
  list(APPEND installable_libs SqrtLibrary)
endif()
install(TARGETS ${installable_libs} DESTINATION lib)
# install include headers
install(FILES MathFunctions.h DESTINATION include)
