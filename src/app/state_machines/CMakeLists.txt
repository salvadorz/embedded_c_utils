#******************************************************************************
#*Copyright (C) 2023 by Salvador Z                                            *
#*                                                                            *
#*****************************************************************************/
#*
#*@author Salvador Z
#*@brief CMakeLists file to add executables targets
#*
add_executable(st_elevator st_elevator.c)
target_link_libraries(st_elevator cbuff)

add_executable(sm_elevator sm_elevator.c)
target_link_libraries(sm_elevator cbuff)

add_executable(sync_thread sync_thread.c)
target_link_libraries(sync_thread pthread)

add_executable(text text.c)
