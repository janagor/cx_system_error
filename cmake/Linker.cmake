macro(cx_system_error_configure_linker project_name)
  set(cx_system_error_USER_LINKER_OPTION
      "DEFAULT"
      CACHE STRING "Linker to be used")
  set(cx_system_error_USER_LINKER_OPTION_VALUES
      "DEFAULT"
      "SYSTEM"
      "LLD"
      "GOLD"
      "BFD"
      "MOLD"
      "SOLD"
      "APPLE_CLASSIC"
      "MSVC")
  set_property(CACHE cx_system_error_USER_LINKER_OPTION PROPERTY STRINGS ${cx_system_error_USER_LINKER_OPTION_VALUES})
  list(
    FIND
    cx_system_error_USER_LINKER_OPTION_VALUES
    ${cx_system_error_USER_LINKER_OPTION}
    cx_system_error_USER_LINKER_OPTION_INDEX)

  if(${cx_system_error_USER_LINKER_OPTION_INDEX} EQUAL -1)
    message(
      STATUS
        "Using custom linker: '${cx_system_error_USER_LINKER_OPTION}', explicitly supported entries are ${cx_system_error_USER_LINKER_OPTION_VALUES}"
    )
  endif()

  set_target_properties(${project_name} PROPERTIES LINKER_TYPE "${cx_system_error_USER_LINKER_OPTION}")
endmacro()
