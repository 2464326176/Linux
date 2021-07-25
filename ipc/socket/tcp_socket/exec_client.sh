#!/bin/bash
int=1
while(( $int<= 128 ))
do
    echo $int
    echo "start connect server "
    num = $int + 9527
    ./client $num & 
    let "int++"
done


