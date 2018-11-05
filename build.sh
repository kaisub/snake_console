#!/bin/bash

# variables
let step_no=0
PROJECT_NAME=snake_console
BUILD_DIR_NAME=$PROJECT_NAME"-build"

# print text colors
COLOR_HEAD='\033[1;33m'
COLOR_SUBHEAD='\033[0;33m'
GREEN='\033[1;32m'
RED='\033[1;31m'
NC='\033[0m' # No Color

# print iteration number and passed text
function printAndIter {
    let step_no=step_no+1
    if [ -z "$2" ]; then
        echo -e $COLOR_SUBHEAD
        echo -e ' '$step_no$1${NC}
    else
        echo -e $1
        echo -e ' '$step_no$2${NC}
    fi
}

# print if last color succeeded or failed
function printCommandSucceeded {
    if [ $? -eq 0 ]; then
        echo -e $1 ${GREEN}[OK]${NC}
    else
        echo -e $1 ${RED}[FAIL]${NC}
    fi
}

# ******************* #
# main body starts here
# ******************* #

echo -e $GREEN
echo -e " Welcome to $RED"$PROJECT_NAME"$GREEN builder"
echo -e " I'll create directory: $RED"$BUILD_DIR_NAME"$GREEN and create binary there"$NC

printAndIter ". --> I'm starting here:"
pwd

printAndIter ". --> removing old binaries"
cd ../
rm -fr 
echo "removing: "$PWD/$BUILD_DIR_NAME
printCommandSucceeded

printAndIter ". --> in build directory, generate makefiles: "
mkdir -p $BUILD_DIR_NAME
cd $BUILD_DIR_NAME
cmake -G "Unix Makefiles" ../$PROJECT_NAME
printCommandSucceeded

printAndIter ". --> building binary:"
make
printCommandSucceeded

printAndIter $COLOR_HEAD ". --> starting binary:"

echo
#./$PROJECT_NAME
echo
