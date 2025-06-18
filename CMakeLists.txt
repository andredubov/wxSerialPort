cmake_minimum_required(VERSION 3.23 FATAL_ERROR)

project(wxSerialPort VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(
        $<$<CONFIG:Release>:/MT>
        $<$<CONFIG:Debug>:/MTd>
        $<$<CONFIG:RelWithDebInfo>:/MT>
        $<$<CONFIG:MinSizeRel>:/MT>
        $<$<NOT:$<OR:$<CONFIG:Release>,$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>,$<CONFIG:MinSizeRel>>>:/MT>)
else()
    set(cmake_find_library_suffixes ".a")
    set(build_shared_libs off)
    set(cmake_exe_linker_flags "-static")
endif()

file(GLOB LIBRARY_SOURCES ${PROJECT_SOURCE_DIR}/library/src/*.cpp)

include(cmake/UpdateSubmodules.cmake) # update the submodules here

set(BOOST_INCLUDE_LIBRARIES asio)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/deps/boost EXCLUDE_FROM_ALL)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/deps/wxWidgets)

# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/deps/wxWidgets)

add_library(${PROJECT_NAME} ${LIBRARY_SOURCES})
target_link_libraries(${PROJECT_NAME} wx::core wx::base Boost::asio)

target_include_directories(${PROJECT_NAME} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/deps/wxWidgets
    ${CMAKE_CURRENT_SOURCE_DIR}/library/inc
)