cmake_minimum_required(VERSION 3.23 FATAL_ERROR)

project(wxSerialPort VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVS)
    add_compile_options(
        $<$<CONFIG:>:/MT>
        $<$<CONFIG:Debug>:/MTd>
        $<$<CONFIG:Release>:/MT>)
else()
    set(cmake_find_library_suffixes ".a")
    set(build_shared_libs off)
    set(cmake_exe_linker_flags "-static")
endif()

file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

set(BOOST_INCLUDE_LIBRARIES asio)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/boost EXCLUDE_FROM_ALL)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/wxWidgets)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/wxWidgets)

add_library(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} wx::core wx::base Boost::asio)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})