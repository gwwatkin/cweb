#!/bin/bash


# TODO make a makefile

SOURCE_FILES='library/hashmap/Hashmap.c
              library/hashmap/MapStrStr.c
              library/vector/VecPtr.c
              library/utils.c'


gcc -g -o bin/tests \
    $SOURCE_FILES \
    tests/test.c \
    -pthread \
    -Lonion
    
echo "Running tests..."


./bin/tests

exit_code=$?


if [ $exit_code -eq 0 ];
then
    echo "Tests successful"
else
    echo "Test failed, exited $exit_code"
fi


gcc -g -o bin/main \
    $SOURCE_FILES \
    main.c \
    -pthread \
    -lonion

./bin/main
