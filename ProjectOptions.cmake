include(CMakeDependentOption)
include(CheckCXXCompilerFlag)

include(CheckCXXSourceCompiles)

macro(cx_system_error_supports_sanitizers)
  # Emscripten doesn't support sanitizers
  if(EMSCRIPTEN)
    set(SUPPORTS_UBSAN OFF)
    set(SUPPORTS_ASAN OFF)
  elseif((CMAKE_CXX_COMPILER_ID MATCHES ".*Clang.*" OR CMAKE_CXX_COMPILER_ID MATCHES ".*GNU.*") AND NOT WIN32)

    message(STATUS "Sanity checking UndefinedBehaviorSanitizer, it should be supported on this platform")
    set(TEST_PROGRAM "int main() { return 0; }")

    # Check if UndefinedBehaviorSanitizer works at link time
    set(CMAKE_REQUIRED_FLAGS "-fsanitize=undefined")
    set(CMAKE_REQUIRED_LINK_OPTIONS "-fsanitize=undefined")
    check_cxx_source_compiles("${TEST_PROGRAM}" HAS_UBSAN_LINK_SUPPORT)

    if(HAS_UBSAN_LINK_SUPPORT)
      message(STATUS "UndefinedBehaviorSanitizer is supported at both compile and link time.")
      set(SUPPORTS_UBSAN ON)
    else()
      message(WARNING "UndefinedBehaviorSanitizer is NOT supported at link time.")
      set(SUPPORTS_UBSAN OFF)
    endif()
  else()
    set(SUPPORTS_UBSAN OFF)
  endif()

  if((CMAKE_CXX_COMPILER_ID MATCHES ".*Clang.*" OR CMAKE_CXX_COMPILER_ID MATCHES ".*GNU.*") AND WIN32)
    set(SUPPORTS_ASAN OFF)
  else()
    if(NOT WIN32)
      message(STATUS "Sanity checking AddressSanitizer, it should be supported on this platform")
      set(TEST_PROGRAM "int main() { return 0; }")

      # Check if AddressSanitizer works at link time
      set(CMAKE_REQUIRED_FLAGS "-fsanitize=address")
      set(CMAKE_REQUIRED_LINK_OPTIONS "-fsanitize=address")
      check_cxx_source_compiles("${TEST_PROGRAM}" HAS_ASAN_LINK_SUPPORT)

      if(HAS_ASAN_LINK_SUPPORT)
        message(STATUS "AddressSanitizer is supported at both compile and link time.")
        set(SUPPORTS_ASAN ON)
      else()
        message(WARNING "AddressSanitizer is NOT supported at link time.")
        set(SUPPORTS_ASAN OFF)
      endif()
    else()
      set(SUPPORTS_ASAN ON)
    endif()
  endif()
endmacro()

macro(cx_system_error_setup_options)
  option(cx_system_error_ENABLE_HARDENING "Enable hardening" ON)
  option(cx_system_error_ENABLE_COVERAGE "Enable coverage reporting" OFF)
  cmake_dependent_option(
    cx_system_error_ENABLE_GLOBAL_HARDENING
    "Attempt to push hardening options to built dependencies"
    ON
    cx_system_error_ENABLE_HARDENING
    OFF)

  cx_system_error_supports_sanitizers()

  if(NOT PROJECT_IS_TOP_LEVEL OR cx_system_error_PACKAGING_MAINTAINER_MODE)
    option(cx_system_error_ENABLE_IPO "Enable IPO/LTO" OFF)
    option(cx_system_error_WARNINGS_AS_ERRORS "Treat Warnings As Errors" OFF)
    option(cx_system_error_ENABLE_SANITIZER_ADDRESS "Enable address sanitizer" OFF)
    option(cx_system_error_ENABLE_SANITIZER_LEAK "Enable leak sanitizer" OFF)
    option(cx_system_error_ENABLE_SANITIZER_UNDEFINED "Enable undefined sanitizer" OFF)
    option(cx_system_error_ENABLE_SANITIZER_THREAD "Enable thread sanitizer" OFF)
    option(cx_system_error_ENABLE_SANITIZER_MEMORY "Enable memory sanitizer" OFF)
    option(cx_system_error_ENABLE_UNITY_BUILD "Enable unity builds" OFF)
    option(cx_system_error_ENABLE_CLANG_TIDY "Enable clang-tidy" OFF)
    option(cx_system_error_ENABLE_CPPCHECK "Enable cpp-check analysis" OFF)
    option(cx_system_error_ENABLE_PCH "Enable precompiled headers" OFF)
    option(cx_system_error_ENABLE_CACHE "Enable ccache" OFF)
  else()
    option(cx_system_error_ENABLE_IPO "Enable IPO/LTO" ON)
    option(cx_system_error_WARNINGS_AS_ERRORS "Treat Warnings As Errors" ON)
    option(cx_system_error_ENABLE_SANITIZER_ADDRESS "Enable address sanitizer" ${SUPPORTS_ASAN})
    option(cx_system_error_ENABLE_SANITIZER_LEAK "Enable leak sanitizer" OFF)
    option(cx_system_error_ENABLE_SANITIZER_UNDEFINED "Enable undefined sanitizer" ${SUPPORTS_UBSAN})
    option(cx_system_error_ENABLE_SANITIZER_THREAD "Enable thread sanitizer" OFF)
    option(cx_system_error_ENABLE_SANITIZER_MEMORY "Enable memory sanitizer" OFF)
    option(cx_system_error_ENABLE_UNITY_BUILD "Enable unity builds" OFF)
    option(cx_system_error_ENABLE_CLANG_TIDY "Enable clang-tidy" ON)
    option(cx_system_error_ENABLE_CPPCHECK "Enable cpp-check analysis" ON)
    option(cx_system_error_ENABLE_PCH "Enable precompiled headers" OFF)
    option(cx_system_error_ENABLE_CACHE "Enable ccache" ON)
  endif()

  if(NOT PROJECT_IS_TOP_LEVEL)
    mark_as_advanced(
      cx_system_error_ENABLE_IPO
      cx_system_error_WARNINGS_AS_ERRORS
      cx_system_error_ENABLE_SANITIZER_ADDRESS
      cx_system_error_ENABLE_SANITIZER_LEAK
      cx_system_error_ENABLE_SANITIZER_UNDEFINED
      cx_system_error_ENABLE_SANITIZER_THREAD
      cx_system_error_ENABLE_SANITIZER_MEMORY
      cx_system_error_ENABLE_UNITY_BUILD
      cx_system_error_ENABLE_CLANG_TIDY
      cx_system_error_ENABLE_CPPCHECK
      cx_system_error_ENABLE_COVERAGE
      cx_system_error_ENABLE_PCH
      cx_system_error_ENABLE_CACHE)
  endif()

endmacro()

macro(cx_system_error_global_options)
  if(cx_system_error_ENABLE_IPO)
    include(cmake/InterproceduralOptimization.cmake)
    cx_system_error_enable_ipo()
  endif()

  cx_system_error_supports_sanitizers()

  if(cx_system_error_ENABLE_HARDENING AND cx_system_error_ENABLE_GLOBAL_HARDENING)
    include(cmake/Hardening.cmake)
    if(NOT SUPPORTS_UBSAN
       OR cx_system_error_ENABLE_SANITIZER_UNDEFINED
       OR cx_system_error_ENABLE_SANITIZER_ADDRESS
       OR cx_system_error_ENABLE_SANITIZER_THREAD
       OR cx_system_error_ENABLE_SANITIZER_LEAK)
      set(ENABLE_UBSAN_MINIMAL_RUNTIME FALSE)
    else()
      set(ENABLE_UBSAN_MINIMAL_RUNTIME TRUE)
    endif()
    message("${cx_system_error_ENABLE_HARDENING} ${ENABLE_UBSAN_MINIMAL_RUNTIME} ${cx_system_error_ENABLE_SANITIZER_UNDEFINED}")
    cx_system_error_enable_hardening(cx_system_error_options ON ${ENABLE_UBSAN_MINIMAL_RUNTIME})
  endif()
endmacro()

macro(cx_system_error_local_options)
  if(PROJECT_IS_TOP_LEVEL)
    include(cmake/StandardProjectSettings.cmake)
  endif()

  add_library(cx_system_error_warnings INTERFACE)
  add_library(cx_system_error_options INTERFACE)

  include(cmake/CompilerWarnings.cmake)
  cx_system_error_set_project_warnings(
    cx_system_error_warnings
    ${cx_system_error_WARNINGS_AS_ERRORS}
    ""
    ""
    ""
    "")

  include(cmake/Linker.cmake)
  # Must configure each target with linker options, we're avoiding setting it globally for now

  if(NOT EMSCRIPTEN)
    include(cmake/Sanitizers.cmake)
    cx_system_error_enable_sanitizers(
      cx_system_error_options
      ${cx_system_error_ENABLE_SANITIZER_ADDRESS}
      ${cx_system_error_ENABLE_SANITIZER_LEAK}
      ${cx_system_error_ENABLE_SANITIZER_UNDEFINED}
      ${cx_system_error_ENABLE_SANITIZER_THREAD}
      ${cx_system_error_ENABLE_SANITIZER_MEMORY})
  endif()

  set_target_properties(cx_system_error_options PROPERTIES UNITY_BUILD ${cx_system_error_ENABLE_UNITY_BUILD})

  if(cx_system_error_ENABLE_PCH)
    target_precompile_headers(
      cx_system_error_options
      INTERFACE
      <vector>
      <string>
      <utility>)
  endif()

  if(cx_system_error_ENABLE_CACHE)
    include(cmake/Cache.cmake)
    cx_system_error_enable_cache()
  endif()

  include(cmake/StaticAnalyzers.cmake)
  if(cx_system_error_ENABLE_CLANG_TIDY)
    cx_system_error_enable_clang_tidy(cx_system_error_options ${cx_system_error_WARNINGS_AS_ERRORS})
  endif()

  if(cx_system_error_ENABLE_CPPCHECK)
    cx_system_error_enable_cppcheck(${cx_system_error_WARNINGS_AS_ERRORS} "" # override cppcheck options
    )
  endif()

  if(cx_system_error_ENABLE_COVERAGE)
    include(cmake/Tests.cmake)
    cx_system_error_enable_coverage(cx_system_error_options)
  endif()

  if(cx_system_error_WARNINGS_AS_ERRORS)
    check_cxx_compiler_flag("-Wl,--fatal-warnings" LINKER_FATAL_WARNINGS)
    if(LINKER_FATAL_WARNINGS)
      # This is not working consistently, so disabling for now
      # target_link_options(cx_system_error_options INTERFACE -Wl,--fatal-warnings)
    endif()
  endif()

  if(cx_system_error_ENABLE_HARDENING AND NOT cx_system_error_ENABLE_GLOBAL_HARDENING)
    include(cmake/Hardening.cmake)
    if(NOT SUPPORTS_UBSAN
       OR cx_system_error_ENABLE_SANITIZER_UNDEFINED
       OR cx_system_error_ENABLE_SANITIZER_ADDRESS
       OR cx_system_error_ENABLE_SANITIZER_THREAD
       OR cx_system_error_ENABLE_SANITIZER_LEAK)
      set(ENABLE_UBSAN_MINIMAL_RUNTIME FALSE)
    else()
      set(ENABLE_UBSAN_MINIMAL_RUNTIME TRUE)
    endif()
    cx_system_error_enable_hardening(cx_system_error_options OFF ${ENABLE_UBSAN_MINIMAL_RUNTIME})
  endif()

endmacro()
