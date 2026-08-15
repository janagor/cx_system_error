include(cmake/CPM.cmake)

# Done as a function so that updates to variables like
# CMAKE_CXX_FLAGS don't propagate out to other
# targets
function(cx_system_error_setup_dependencies)

  # For each dependency, see if it's
  # already been provided to us by a parent project

  if(NOT TARGET Catch2::Catch2WithMain)
    cpmaddpackage(
      NAME
      Catch2
      VERSION
      3.12.0
      GITHUB_REPOSITORY
      "catchorg/Catch2"
      SYSTEM
      YES)
  endif()

endfunction()
