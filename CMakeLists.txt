cmake_minimum_required(VERSION 3.29)

# Disable modules support, this is broken with clang-tidy at the moment
cmake_policy(SET CMP0155 OLD)

# This template attempts to be "fetch_content"-able
# so that it works well with tools like CPM or other
# manual dependency management

# Only set the cxx_standard if it is not set by someone else
if(NOT DEFINED CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 23)
endif()

# strongly encouraged to enable this globally to avoid conflicts between
# -Wpedantic being enabled and -std=c++20 and -std=gnu++20 for example
# when compiling with PCH enabled
set(CMAKE_CXX_EXTENSIONS OFF)

# Set the project name and language
project(
  cx_system_error
  VERSION 0.0.2
  DESCRIPTION ""
  HOMEPAGE_URL "https://github.com/janagor/cx_system_error"
  LANGUAGES CXX C)

include(cmake/PreventInSourceBuilds.cmake)
include(cmake/Emscripten.cmake)
include(ProjectOptions.cmake)

cx_system_error_setup_options()

cx_system_error_global_options()
include(Dependencies.cmake)
cx_system_error_setup_dependencies()

cx_system_error_local_options()

# don't know if this should be set globally from here or not...
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

set(GIT_SHA
    "Unknown"
    CACHE STRING "SHA this build was generated from")
string(
  SUBSTRING "${GIT_SHA}"
            0
            8
            GIT_SHORT_SHA)

target_compile_features(cx_system_error_options INTERFACE cxx_std_${CMAKE_CXX_STANDARD})

add_library(cx_system_error::cx_system_error_options ALIAS cx_system_error_options)
add_library(cx_system_error::cx_system_error_warnings ALIAS cx_system_error_warnings)

#add_library(cx_system_error::cx_system_error_options INTERFACE IMPORTED)
#add_library(cx_system_error::cx_system_error_warnings INTERFACE IMPORTED)

# configure files based on CMake configuration options
add_subdirectory(configured_files)

# Adding the src:
add_subdirectory(src)

# Create unified web deployment directory (for WASM builds)
if(EMSCRIPTEN)
  cx_system_error_create_web_dist()
endif()

# Don't even look at tests if we're not top level
if(NOT PROJECT_IS_TOP_LEVEL)
  return()
endif()

include(cmake/Format.cmake)
vkgsplat_enable_formatting()

# Adding the tests:
include(CTest)

if(BUILD_TESTING)
  message(AUTHOR_WARNING "Building Tests. Be sure to check out test/constexpr_tests.cpp for constexpr testing")
  add_subdirectory(test)
endif()

if(cx_system_error_BUILD_FUZZ_TESTS)
  message(AUTHOR_WARNING "Building Fuzz Tests, using fuzzing sanitizer https://www.llvm.org/docs/LibFuzzer.html")
  if(NOT cx_system_error_ENABLE_SANITIZER_ADDRESS AND NOT cx_system_error_ENABLE_SANITIZER_THREAD)
    message(WARNING "You need asan or tsan enabled for meaningful fuzz testing")
  endif()
  add_subdirectory(fuzz_test)

endif()

# If MSVC is being used, and ASAN is enabled, we need to set the debugger environment
# so that it behaves well with MSVC's debugger, and we can run the target from visual studio
if(MSVC)
  get_all_installable_targets(all_targets)
  message("all_targets=${all_targets}")
  set_target_properties(${all_targets} PROPERTIES VS_DEBUGGER_ENVIRONMENT "PATH=$(VC_ExecutablePath_x64);%PATH%")
endif()

# set the startup project for the "play" button in MSVC
if(TARGET tests)
  set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT tests)
endif()

if(CMAKE_SKIP_INSTALL_RULES)
  return()
endif()

include(cmake/PackageProject.cmake)

cx_system_error_package_project(
  TARGETS
  cx_system_error_lib
  cx_system_error_options
  cx_system_error_warnings
  PUBLIC_INCLUDES
  ${PROJECT_SOURCE_DIR}/include
)

# Experience shows that explicit package naming can help make it easier to sort
# out potential ABI related issues before they start, while helping you
# track a build to a specific GIT SHA
set(CPACK_PACKAGE_FILE_NAME
    "${CMAKE_PROJECT_NAME}-${CMAKE_PROJECT_VERSION}-${GIT_SHORT_SHA}-${CMAKE_SYSTEM_NAME}-${CMAKE_BUILD_TYPE}-${CMAKE_CXX_COMPILER_ID}-${CMAKE_CXX_COMPILER_VERSION}"
)

include(CPack)
