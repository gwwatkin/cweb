#!/bin/bash



# find . -type f -print0 | xargs -0 sed -i 's/VecPtr/vector/g'
#
# to replace: 
# Route_/RouteNode_
# vector_/Vector_
# hashmap/Hashmap

PROGRAM_NAME="\\033[32m[run.sh]\\033[0m"



LIBRARY_SOURCES=" \
    ./library/utils.c \
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


ONION_SHARED=vendor/onion/build/src/onion/libonion.so;

# compile onion
if [ "$1" = "compile-onion" ];
then
    echo -e "$PROGRAM_NAME Compiling libonion";

    cd vendor/onion
    mkdir build
    cd build
    cmake ..
    make onion
    cd ../../..
fi



if [ "$1" = "" ];
then
    echo -e "$PROGRAM_NAME Compiling the executable";

    gcc -L$ONION_SHARED -Wl,-rpath=$ONION_SHARED $MAIN_SOURCES -g -Wall -o ./bin/main -lonion;


    echo -e "$PROGRAM_NAME Running the executable";
    ./bin/main 3000;
fi

if [ "$1" = "test" ];
then
    echo -e "$PROGRAM_NAME Compiling the tests";
    
    gcc -L$ONION_SHARED -Wl,-rpath=$ONION_SHARED -g $TEST_SOURCES -Wall -o ./bin/tests -lonion;


    echo -e "$PROGRAM_NAME Running the tests";
    ./bin/tests;
fi




