#!/bin/bash
int=1
while(( $int<= 128 ))
do
    echo $int
    echo "start connect server "
    ./client &
    let "int++"
done


