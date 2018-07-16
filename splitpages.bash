#!/bin/bash
# This script extract pages from a Unitel disc image that has been converted by
# the ebcdic2vdt.bash script. It won't work on raw Unitel disc images.
# It takes one parameter: the disc image file name.
# The generated files are written in the current directory.
# It uses the searchpage executable which must be in the same directory.
SOURCE="$1"

# The searchpage command must be in the same directory than this script.
DIR="$(cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd)"

cat "$SOURCE" | "$DIR/searchpage" | while read range
do
    cut --bytes="$range" "$SOURCE" > "$(basename "$SOURCE")-$range.vdt"
done