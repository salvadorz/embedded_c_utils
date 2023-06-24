#******************************************************************************
#*Copyright (C) 2023 by Salvador Z                                            *
#*                                                                            *
#*****************************************************************************/
#*
#*@author Salvador Z
#*@brief CMakeLists file for tesst the Linked List library
#*
add_executable(test_llist test_llist.c)
target_link_libraries(test_llist uTest llist)

### Test Cases ###
add_test(NAME test_llist_lib COMMAND test_llist)


install(TARGETS test_llist
        RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/test)