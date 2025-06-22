cmake_minimum_required(VERSION 3.23 FATAL_ERROR)

project(wxserialport VERSION 1.0.0)

if(WIN32)
    # Minimum version Windows XP SP3
    add_definitions(-D_WIN32_WINNT=0x0501 -D_WIN32_IE=0x0501)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON) 
set(CMAKE_CXX_EXTENSIONS OFF)

set(Boost_NO_WARN_NEW_VERSIONS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_DEBUG_LIBS ON)

if(MSVC)
    set(Boost_USE_STATIC_LIBS ON)
    set(Boost_USE_STATIC_RUNTIME ON)
else()
    set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
    set(BUILD_SHARED_LIBS OFF)
    if(MINGW)
        set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc -static-libstdc++ --enable-stdcall-fixup")
    else()
        set(CMAKE_EXE_LINKER_FLAGS "-static")
    endif()
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