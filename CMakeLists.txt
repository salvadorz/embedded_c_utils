#******************************************************************************
#*Copyright (C) 2023 by Salvador Z                                            *
#*                                                                            *
#*****************************************************************************/
#*
#*@author Salvador Z
#*@brief CMakeLists file to create a CMake project
#*
cmake_minimum_required(VERSION 3.0.0)
project(Embedded_C_Utils
  VERSION 0.1
  DESCRIPTION "Project with common utilities for embedded systems"
  LANGUAGES C CXX ASM)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

### General Project Structure ###

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/lib/)

### Project Source Tree ###
add_subdirectory("src")
