project(JVCR-ECM-01-PYTHON C)

find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

add_executable(JVCR-ECM-01-PYTHON jvcr.h jvcr.c main.c py_display.h py_display.c py_input.h py_input.c)

target_link_libraries(JVCR-ECM-01-PYTHON ${PYTHON_LIBRARIES} ${OPENGL_gl_LIBRARY} glfw JVCR-ECM-01)