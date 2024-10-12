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

# include cmake check feature
include(CheckCXXSourceCompiles)
## check whether log is available
check_cxx_source_compiles("
  #include <cmath>
  int main() {
    std::log(1.0);
    return 0;
  }
" HAVE_LOG)
## check whether exp is available
check_cxx_source_compiles("
  #include <cmath>
  int main() {
    std::exp(1.0);
    return 0;
  }
" HAVE_EXP)
## log and exp both exist, define "HAVE_LOG" and "HAVE_EXP" macro
if(HAVE_LOG AND HAVE_EXP)
  target_compile_definitions(${MathFunctions_Module_NAME} PRIVATE "HAVE_LOG" "HAVE_EXP")
endif()
