cmake_minimum_required(VERSION 3.12)
project(pd4)

set( CMAKE_VERBOSE_MAKEFILE on)
if(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
elseif(UNIX AND NOT APPLE)
    set(CMAKE_CXX_FLAGS -pthread)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wpedantic -Wextra")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wpedantic -Wextra")
endif()

add_executable(pd4 main.cpp)