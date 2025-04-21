cmake_minimum_required(VERSION 3.15)
project(torControl VERSION 1.0.0 LANGUAGES CXX)

# Create the library target
add_library(torControl src/torControl.cpp)

# Set C++ standard
target_compile_features(torControl PUBLIC cxx_std_17)

# Public headers
target_include_directories(torControl
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

include(CMakePackageConfigHelpers)

# Create a version file
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/torControlConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion
)

# Create a config file for find_package
configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/torControlConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/torControlConfig.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/torControl
)

install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/torControlConfig.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/torControlConfigVersion.cmake"
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/torControl
)


install(TARGETS torControl
  EXPORT torControlTargets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)


install(EXPORT torControlTargets
  FILE torControlTargets.cmake
  NAMESPACE torControl::         # Must match above!
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/torControl
)