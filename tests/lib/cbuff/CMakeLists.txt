#******************************************************************************
#*Copyright (C) 2023 by Salvador Z                                            *
#*                                                                            *
#*****************************************************************************/
#*
#*@author Salvador Z
#*@brief CMakeLists file to add all test cases for current lib
#*
add_executable(test_cbuff test_cbuff.c)
target_link_libraries(test_cbuff uTest cbuff)

### Test Cases ###
add_test(NAME test_cbuff_lib COMMAND test_cbuff)

#set (passRegex "PASS")
#set (failRegex "FAIL")

#set_tests_properties(test_cbuff_lib PROPERTIES
#  FAIL_REGULAR_EXPRESSION "[^a-z]FAIL"
#)

#set_property (TEST test_cbuff_lib
#              PROPERTY PASS_REGULAR_EXPRESSION "${passRegex}")
#set_property (TEST test_cbuff_lib
#              PROPERTY FAIL_REGULAR_EXPRESSION "${failRegex}")


install(TARGETS test_cbuff
        RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/test)