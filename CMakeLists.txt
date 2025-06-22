cmake_minimum_required(VERSION 3.23 FATAL_ERROR)

project(wxserialport VERSION 1.0.0)

option(wxserialport_USE_SHARED "Use shared libraries" ON)

if(WIN32)
    add_definitions(-D_WIN32_WINNT=0x0501 -D_WIN32_IE=0x0501) # Minimum version Windows XP SP3
endif()

set(Boost_NO_WARN_NEW_VERSIONS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_DEBUG_LIBS ON)

if(wxserialport_USE_SHARED)
    set(Boost_USE_STATIC_LIBS OFF)
    set(Boost_USE_STATIC_RUNTIME OFF)
    set(wxWidgets_CONFIG_OPTIONS "")
else()
    set(Boost_USE_STATIC_LIBS ON)
    set(Boost_USE_STATIC_RUNTIME ON)
    set(wxWidgets_CONFIG_OPTIONS --static=yes)
endif()

file(GLOB LIBRARY_SOURCES ${PROJECT_SOURCE_DIR}/library/src/*.cpp)

add_library(${PROJECT_NAME} STATIC ${LIBRARY_SOURCES})

find_package(Boost 1.69 REQUIRED COMPONENTS system)
if(Boost_FOUND)
    target_link_libraries(${PROJECT_NAME} PRIVATE 
        Boost::system
    )
    target_include_directories(${PROJECT_NAME} PRIVATE
        ${Boost_INCLUDE_DIRS}
    )
else()
    message(FATAL_ERROR "Boost not found!")
endif()

find_package(wxWidgets 3.0 REQUIRED COMPONENTS core base)
if(wxWidgets_FOUND)
    include(${wxWidgets_USE_FILE})
    target_link_libraries(${PROJECT_NAME} PUBLIC 
        ${wxWidgets_LIBRARIES}
    )
    target_include_directories(${PROJECT_NAME} PUBLIC 
        ${wxWidgets_INCLUDE_DIRS}
    )
    target_compile_definitions(${PROJECT_NAME} PUBLIC
        ${wxWidgets_DEFINITIONS}
        wxUSE_UNICODE_MSLU=1  # Required for Unicode on XP
    )
else()
    message(FATAL_ERROR "wxWidgets not found!")
endif()

target_include_directories(${PROJECT_NAME} PUBLIC 
    ${PROJECT_SOURCE_DIR}/library/inc
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)