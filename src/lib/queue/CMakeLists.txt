#******************************************************************************
#*Copyright (C) 2023 by Salvador Z                                            *
#*                                                                            *
#*****************************************************************************/
#*
#*@author Salvador Z
#*@brief CMakeLists file to add Queue Class library
#*
add_library(queue STATIC queue.cpp)
target_link_libraries(queue)