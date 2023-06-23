#******************************************************************************
#*Copyright (C) 2023 by Salvador Z                                            *
#*                                                                            *
#*****************************************************************************/
#*
#*@author Salvador Z
#*@brief CMakeLists file to configure the formatting by using clang-format
#*

#######################
# Clang-format Module #
#######################
# This module adds three targets to your build: format-clang, format-all and format-patch
#
# The main functionality of this module is to provide a convenient way to format your source code using clang-format.
# It introduces three targets:
#   - "format-clang" target: Formats the source code files in the specified directories according to clang-format rules.
#   - "format-patch" target: Generates patch files for the modified source code files that need formatting.
#   - "format-all"   target: Formats all source code by performing a searh on whole project using clang-format.
#
# You can control the behavior of clang-format by setting the following variables
# before including this module:
#   - CLANG_FORMAT_EXCLUDE_DIRS: A CMake list of directories to exclude from formatting.
#     By default, no directories are excluded.
#   - CLANG_FORMAT_INCLUDE_DIRS: A CMake list of directories to include in formatting.
#     By default, the "src" and "test" directories are included.
#   - CLANG_FORMAT_FILETYPES: A CMake list of file types to include in formatting,
#     specified as globs (e.g., "*.c").
#     By default, the module formats *.c, *.h, *.cpp, and *.hpp files.
#
# You can override the default values by setting the variables mentioned above.
# If you want to use the default values for CLANG_FORMAT_INCLUDE_DIRS and CLANG_FORMAT_FILETYPES
# but add additional directories or files, you can set these variables:
#   - CLANG_FORMAT_ADDITIONAL_DIRS
#   - CLANG_FORMAT_ADDITIONAL_FILETYPES

if(ENABLE_FORMAT)
  find_program(CLANG_FORMAT clang-format)
endif()

set(CLANG_FORMAT_ADDITIONAL_DIRS tests include)
#set(CLANG_FORMAT_ADDITIONAL_FILETYPES "*.cc")

if(CLANG_FORMAT)
  ### Supply argument defaults
  if(NOT CLANG_FORMAT_EXCLUDE_DIRS)
    set(CLANG_FORMAT_EXCLUDE_DIRS "")
  endif()

  if(NOT CLANG_FORMAT_INCLUDE_DIRS)
    set(CLANG_FORMAT_INCLUDE_DIRS src CACHE STRING "CMake list of directories to format using clang-format.")
  endif()

  if(NOT CLANG_FORMAT_FILETYPES)
    set(CLANG_FORMAT_FILETYPES "*.c" "*.h" "*.cpp" "*.hpp" CACHE STRING "CMake list of file types to format using clang-format.")
  endif()

  if(CLANG_FORMAT_ADDITIONAL_DIRS)
    list(APPEND CLANG_FORMAT_INCLUDE_DIRS ${CLANG_FORMAT_ADDITIONAL_DIRS})
  endif()

  if(CLANG_FORMAT_ADDITIONAL_FILETYPES)
    list(APPEND CLANG_FORMAT_FILETYPES ${CLANG_FORMAT_ADDITIONAL_FILETYPES})
  endif()

  ### Convert variables into script format
  if(CLANG_FORMAT_EXCLUDE_DIRS)
    string(REPLACE ";" "," CLANG_FORMAT_EXCLUDE_ARG "${CLANG_FORMAT_EXCLUDE_DIRS}")
    set(CLANG_FORMAT_EXCLUDE_ARG "-e ${CLANG_FORMAT_EXCLUDE_ARG}")
  else()
    set(CLANG_FORMAT_EXCLUDE_ARG "")
  endif()

  string(REPLACE ";" "," CLANG_FORMAT_INCLUDE_ARG "${CLANG_FORMAT_INCLUDE_DIRS}")
  string(REPLACE ";" "," CLANG_FORMAT_FILETYPES_ARG "${CLANG_FORMAT_FILETYPES}")

  set(clang_format_args
    ${CLANG_FORMAT_EXCLUDE_ARG}
    ${CLANG_FORMAT_INCLUDE_ARG}
    ${CLANG_FORMAT_FILETYPES_ARG}
  )
  message(STATUS " clang-format args: ${clang_format_args}")

  add_custom_target(format-clang
    COMMAND ${CMAKE_SOURCE_DIR}/scripts/clang_format.sh
      # common args
      ${clang_format_args}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  )

  add_custom_target(format-patch
    COMMAND ${CMAKE_CURRENT_LIST_DIR}/../../scripts/clang_format.sh
      # Enable patch file
      -p
      # Common args
      ${clang_format_args}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  )

  add_custom_target(format-all
    COMMAND ${CMAKE_CURRENT_LIST_DIR}/../../scripts/clang_format.sh
      # Enable patch file
      -a
      # Common args
      ${clang_format_args}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  )
else()
  # message(SEND_ERROR "clang-format not installed!")
  message(WARNING "[NOK] Clang-format is not installed. Formatting targets are disabled.")
endif()