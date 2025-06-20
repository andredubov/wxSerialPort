cmake_minimum_required(VERSION 3.23 FATAL_ERROR)

project(wxserialport VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB LIBRARY_SOURCES ${PROJECT_SOURCE_DIR}/library/src/*.cpp)

add_library(${PROJECT_NAME} STATIC ${LIBRARY_SOURCES})

find_package(Boost 1.88 REQUIRED COMPONENTS system thread)
if(Boost_FOUND)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${Boost_LIBRARIES})
else()
    message("Boost not found!")
endif()

find_package(wxWidgets 3.0 REQUIRED COMPONENTS core base)
if(wxWidgets_FOUND)
    include(${wxWidgets_USE_FILE})
    target_link_libraries(${PROJECT_NAME} PUBLIC ${wxWidgets_LIBRARIES})
else()
    message("wxWidgets not found!")
endif()

target_include_directories(${PROJECT_NAME} PUBLIC 
    ${PROJECT_SOURCE_DIR}/library/inc
    ${Boost_INCLUDE_DIRS}
)