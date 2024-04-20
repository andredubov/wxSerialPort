cmake_minimum_required(VERSION 3.23 FATAL_ERROR)

project(wxSerialPort VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/wxWidgets)

add_library(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} wx::core wx::base)


target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})