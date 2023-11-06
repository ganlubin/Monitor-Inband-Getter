cmake_minimum_required(VERSION 3.10)
project(Monitor-Inband-Getter VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

include_directories(.)

set(SOURCES
    main.cpp
    tools.cpp
    jsonPackage.cpp
    Procps.cpp
    Boost_process.cpp
)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build)

find_library(PROCPS_LIBRARY NAMES procps)
if(NOT PROCPS_LIBRARY)
    message(FATAL_ERROR "procps library not found")
endif()

add_executable(main ${SOURCES})

target_link_libraries(main ${PROCPS_LIBRARY})