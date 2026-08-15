add_library(cx_system_error_lib INTERFACE)
add_library(cx_system_error::cx_system_error ALIAS cx_system_error_lib)

target_include_directories(cx_system_error_lib INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                                                         $<INSTALL_INTERFACE:include>)

target_compile_features(cx_system_error_lib INTERFACE cxx_std_${CMAKE_CXX_STANDARD})
