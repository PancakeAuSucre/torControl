cmake_minimum_required(VERSION 3.5...3.16)

project(torControl)

set(CMAKE_CXX_STANDARD 17)


set(SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/torControl.cpp)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_library(${PROJECT_NAME} ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIR})
