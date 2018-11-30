cmake_minimum_required(VERSION 3.6)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 11)
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -Werror -Wextra -Wzero-as-null-pointer-constant -Winit-self -Wswitch-default -Wfloat-equal -Wno-unused-parameter -fPIC -march=native")
set( CMAKE_VERBOSE_MAKEFILE on )
set(CMAKE_DIR "${PROJECT_SOURCE_DIR}/CMake")
list(APPEND CMAKE_MODULE_PATH ${CMAKE_DIR})

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(PNG REQUIRED)

set(PROJECT_HEADERS_DIR ${PROJECT_SOURCE_DIR}/include)
set(PROJECT_SOURCES_DIR ${PROJECT_SOURCE_DIR}/src)
set(PY_PROJECT_SOURCES_DIR ${PROJECT_SOURCE_DIR}/python)
set(TEST_SOURCES_DIR ${PROJECT_SOURCE_DIR}/tests)

file(GLOB_RECURSE HEADERS ${PROJECT_HEADERS_DIR}/*.h)
file(GLOB_RECURSE SOURCES ${PROJECT_SOURCES_DIR}/*.c)
file(GLOB_RECURSE PY_SOURCES ${PY_PROJECT_SOURCES_DIR}/*.c)
file(GLOB_RECURSE TEST_SOURCES ${TEST_SOURCES_DIR}/*.cpp)

include_directories(${PROJECT_HEADERS_DIR})
include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${PNG_INCLUDE_DIR})

add_subdirectory(src)
add_subdirectory(example)
add_subdirectory(python)
#add_subdirectory(tests)