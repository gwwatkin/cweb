#!/bin/bash


# TODO Run all these replacements using
# find . -type f -print0 | xargs -0 sed -i 's/newstr/oldstr/g'
#
# vector_lenght/vector_size
# Route_/RouteNode_
# vector_/Vector_
# hashmap/Hashmap


PROGRAM_NAME="run.sh"

#add the color
PROGRAM_PRETTY_NAME="\\033[32m[$PROGRAM_NAME]\\033[0m"



LIBRARY_SOURCES=" \
    ./library/utils.c \
    ./library/Path.c \
    ./library/vector/vector.c \
    ./library/hashmap/hashmap.c \
    ./library/server/AppKernel.c \
    ./library/server/Route.c \
    ./library/server/Request.c \
    ./library/server/Response.c \
    ./library/server/Server.c \
    ./library/server/App.c \
"

MAIN_SOURCES="$LIBRARY_SOURCES ./main.c"
TEST_SOURCES="$LIBRARY_SOURCES ./tests/test.c"

MAIN_EXECUTABLE="./bin/main"
TESTS_EXECUTABLE="./bin/tests"

DEFAULT_PORT=3000



CFLAGS="-g -Wall"
ONION_LINKER_FLAGS="-Wl,-rpath=./vendor/onion/build/src/onion -I./vendor/onion/src -L./vendor/onion/build/src/onion -lonion"


if [ ! -d "vendor" ];
then
    mkdir vendor
fi

if [ ! -d "bin" ];
then
    mkdir bin
fi


if [ ! -f "vendor/onion/build/src/onion/libonion.so" ];
then
    
    
    
    echo -e "$PROGRAM_PRETTY_NAME Downloading libonion"

    cd vendor
    
        git clone https://github.com/davidmoreno/onion.git
        git checkout tag/v0.8
    cd ..

    echo -e "$PROGRAM_PRETTY_NAME Compiling libonion"
    
    cd vendor/onion
    mkdir build
    cd build
    cmake ..
    make onion
    cd ../../..
fi



if [ "$1" = "" ];
then
    echo -e "$PROGRAM_PRETTY_NAME Compiling the executable"

    gcc $MAIN_SOURCES $CFLAGS -o $MAIN_EXECUTABLE $ONION_LINKER_FLAGS


    echo -e "$PROGRAM_PRETTY_NAME Running the executable"
    
    $MAIN_EXECUTABLE $DEFAULT_PORT
fi

if [ "$1" = "test" ];
then
    echo -e "$PROGRAM_PRETTY_NAME Compiling the tests"
    
    gcc $TEST_SOURCES $CFLAGS -o $TESTS_EXECUTABLE $ONION_LINKER_FLAGS


    echo -e "$PROGRAM_PRETTY_NAME Running the tests"
    
    $TESTS_EXECUTABLE
    
fi




