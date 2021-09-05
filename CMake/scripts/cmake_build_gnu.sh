#! /bin/bash

# Colors
CYAN='\033[0;35m'
RED='\033[0;31m'
NC='\033[0m'
# Colored Text
ERROR=${RED}[ERROR]${NC}


echo "##############################"
echo -e "### ${CYAN}CMake GNU Build Script${NC} ###"
echo "##############################"
if [[ $PWD == */CMake ]]
then
    cmake -S . -B "out/build"
else
    echo $PWD
    echo -e "${ERROR} Wrong directory!"
    echo -e "${ERROR} Go to: <project-path>/CMake";
fi
