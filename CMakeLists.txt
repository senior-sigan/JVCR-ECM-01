cmake_minimum_required(VERSION 3.12)
project(JVCR-PC-01 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/CMake")

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(${OPENGL_INCLUDE_DIR})

add_executable(${PROJECT_NAME} src/main.c)

target_link_libraries(${PROJECT_NAME} ${OPENGL_gl_LIBRARY} glfw)