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

### Build Options ###
option(ENABLE_FORMAT  "Enable format analysis with clang-format" ON)
option(ENABLE_COVERAGE  "Enable code coverage report and HTML  " OFF)
# Automated Code Coverage using GCOV, LCOV and GENHTML

### General Configuration ###

set_property(GLOBAL PROPERTY C_STANDARD   11)
set_property(GLOBAL PROPERTY CXX_STANDARD 17)

set(CMAKE_C_OUTPUT_EXTENSION_REPLACE   ON)
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON)

### Enabling testig for current directory and below
enable_testing()

### Compiler Flags Configuration ###

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_FLAGS "-Wall -Wextra ")
set(CMAKE_C_FLAGS_DEBUG "-g -O0")
set(CMAKE_C_FLAGS_RELEASE "-O3")

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

### Enabling CMAKE Modules
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

##########################
# Enable Static Analysis #
##########################
if(ENABLE_FORMAT)
  include(analysis/clang-format)
endif()
if(ENABLE_COVERAGE)
  include(analysis/code-coverage)
  APPEND_COVERAGE_COMPILER_FLAGS()
endif()

### General Project Structure ###

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/lib/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/uTest/lib/)

# Create an output dir in CMAKE_BINARY_DIR
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE})

### Project Source Tree ###
add_subdirectory("src")
add_subdirectory("uTest")
add_subdirectory("tests")