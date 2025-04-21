cmake_minimum_required(VERSION 2.8)

project(torControl)

set(SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/torControl.cpp)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_library(${PROJECT_NAME} ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)