#******************************************************************************
#*Copyright (C) 2023 by Salvador Z                                            *
#*                                                                            *
#*****************************************************************************/
#*
#*@author Salvador Z
#*@brief CMakeLists file to add all Circular/ring buffer implementation
#*
add_library(cbuff STATIC cbuff.c)
target_link_libraries(cbuff)