#!/bin/bash
# Script to run clang-format.
# Author: Salvador Z.
# format.sh [options] DIRS TYPES
#
# This script is used to format source code files in specified directories using a specific set of file types.
#
# Required arguments:
#   - DIRS:  A comma-separated list of directories to search for files in.
#   - TYPES: A comma-separated list of file types to search for, specified as globs (e.g., *.c, *.h, *.cpp, *.hpp).
#
# Optional arguments:
#   -e: Specifies a comma-separated list of directories to exclude from formatting.
#   -p: Generates a patch file using 'git'.
#   -a: Performs a search of source code files in current project directory
#
# Example usage:
#   format.sh -e src/pid,src/external src,include *.c,*.h,*.cpp,*.hpp
# NOTE: Due to limitations of 'getopts', optional arguments must precede positional arguments.
#
## Processing strategy for separating CSVs is derived from:
## https://stackoverflow.com/questions/918886/how-do-i-split-a-string-on-a-delimiter-in-bash#tab-top

set -e

EXCLUDES_ARGS=""
PATCH=false
ALL=false

# Usage helper
print_usage() {
  echo "Usage: format.sh [options] DIRS TYPES"
  echo "Options:"
  echo "  -e: Specifies a comma-separated list of directories to exclude from formatting."
  echo "  -p: Generates a patch file using 'git'."
  echo "  -a: Performs a search of source code files in the current project directory."
  echo ""
  echo "Example usage:"
  echo "  format.sh -e src/pid,src/external src,include *.c,*.h,*.cpp,*.hpp"
}

while getopts "e:pa" opt; do
  case $opt in
    e) EXCLUDES_ARGS="$OPTARG"
    ;;
    p) PATCH=true
    ;;
    a) ALL=true
    ;;
    \?) print_usage; exit 1 >&2
    ;;
  esac
done

# Shift off the getopts args, leaving us with positional args
shift $((OPTIND -1))

# Make a search on whole project if -a is used
if [ "$ALL" = true ]; then
  sources=$(find . -type f \( -name "*.c" -o -name "*.cpp" -o -name "*.h" -o -name "*.hpp" \) ! -path "./build/*" ! -path "./artifacts/*")
  echo "Running clang-format on all source files from the project"
  clang-format --dry-run --ferror-limit=3 -style=file -i -fallback-style=LLVM $sources
  exit 0
fi

# Parse $1 into a list of directories
DIRS=$(printf " %s" "${1//,/ }")

# Parse $2 into file-type arguments
FILE_TYPES=$(printf " -o -iname %s" "${2//,/ -o -iname }")

# Parse $3 into the exclude arguments
if [[ -n $EXCLUDES_ARGS ]]; then
  EXCLUDES=$(printf " -path %s" "${EXCLUDES_ARGS//,/ -o -path }")
	# Create the final argument string
	EXCLUDES="-type d \( $EXCLUDES \) -prune"
else
	# Remove the initial `-o` argument for the first file type if there are no excludes,
	# otherwise the rules will not be properly parsed
	FILE_TYPES=${FILE_TYPES:3:${#FILE_TYPES}}
fi

echo "DIRS:${DIRS}"
echo "EXCLUDES: ${EXCLUDES}"
echo "FILE_TYPES: ${FILE_TYPES}"

eval find $DIRS $EXCLUDES -type f $FILE_TYPES \
	| xargs clang-format -style=file -i -fallback-style=LLVM

if [ "$PATCH" == true ]; then
	git diff > clang_format.patch

	# Delete if 0 size
	if [ ! -s clang_format.patch ]
	then
		rm clang_format.patch
	fi
fi

exit 0