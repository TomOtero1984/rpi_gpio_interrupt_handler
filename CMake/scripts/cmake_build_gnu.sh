#! /bin/bash


echo "### CMake GNU Build Script ###"

if [[ $PWD == *CMake ]]
then
    cmake -S . -B out/build
else
    echo "Wrong Directory!"
fi
