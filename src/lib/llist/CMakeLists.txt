#******************************************************************************
#*Copyright (C) 2023 by Salvador Z                                            *
#*                                                                            *
#*****************************************************************************/
#*
#*@author Salvador Z
#*@brief CMakeLists file to create linked list target for library
#*
add_library(llist STATIC llist.c)
target_include_directories(llist PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(llist)