project(JVCR-ECM-01-TEST C CXX)
include(ConfigureGTest)

add_executable(JVCR-ECM-01-TEST ${TEST_SOURCES})

target_link_libraries(JVCR-ECM-01-TEST JVCR-ECM-01 m glfw ${OPENGL_gl_LIBRARY} gtest_main gtest)

#add_test(NAME JVCR-ECM-01-TEST_test COMMAND JVCR-ECM-01-TEST)