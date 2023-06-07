#******************************************************************************
#*Copyright (C) 2023 by Salvador Z                                            *
#*                                                                            *
#*****************************************************************************/
#*
#*@author Salvador Z
#*@brief CMakeLists file to add Interpolation estimation lib
#*
add_library(interpolate STATIC interpolate.c)
target_link_libraries(interpolate)