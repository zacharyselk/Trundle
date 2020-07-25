#!/bin/bash

# Save current directory
OLD_DIR=${pwd}

# Move to the directory where the bash script is located
cd $(dirname $0)

# Move to the build directory
mkdir -p ../build
cd ../build


# TODO: Add help argument
if [ "$1" = "clean" ]
then
    cd ..
    echo "Removing $(pwd)/bin/*"
    rm -rf bin/*
    echo "Removing $(pwd)/lib/*"
    rm -rf lib/*
    echo "Removing $(pwd)/build"
else
    echo ""
    echo "-----------------------------Building the Engine--------------------------------"
    cmake .. -DBUILD_LIB=ON
    cmake --build .
    echo "--------------------------------------------------------------------------------"

    echo -e "\n"
    echo "-----------------------------Building the Driver--------------------------------"
    cmake .. -DBUILD_LIB=OFF
    cmake --build .
    echo "--------------------------------------------------------------------------------"
    echo ""
fi

# Return to original directory
cd $OLD_DIR

echo -e "\nFinished"
