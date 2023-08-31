#******************************************************************************
#*Copyright (C) 2023 by Salvador Z                                            *
#*                                                                            *
#*****************************************************************************/
#*
#*@author Salvador Z
#*@brief CMakeLists file to add executables targets
#*
add_executable(pid pid.c)
target_link_libraries(pid -lglut -lGLU -lGL)

add_executable(plot plot.c shader_utils.c)
target_link_libraries(plot -lm -lglut -lGLEW -lGLU -lGL)