cmake_minimum_required(VERSION 3.10)
include(cmake_stuff/settings.cmake)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} sos.cpp)

configure_file(${PROJECT_SOURCE_DIR}/cmake_stuff/cmakevariables.h.in @ONLY)

message("SOS")