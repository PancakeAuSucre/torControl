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
