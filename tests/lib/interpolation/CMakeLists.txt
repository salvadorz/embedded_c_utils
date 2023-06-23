#******************************************************************************
#*Copyright (C) 2023 by Salvador Z                                            *
#*                                                                            *
#*****************************************************************************/
#*
#*@author Salvador Z
#*@brief CMakeLists file to add all test cases for current lib
#*
add_executable(test_interpolate test_interpolate.c)
target_link_libraries(test_interpolate uTest interpolate)

### Test Cases ###
add_test(NAME test_interpolate_lib COMMAND test_interpolate)


install(TARGETS test_interpolate
        RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/test)