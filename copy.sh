#!/bin/bash

cpPath="./../../../../../sanity_check/"

if [ $# != 0 ]
then
  cpPath=$1
  exit 1
fi

cp "./main.cpp" $cpPath

lst1=$(find . -name "*.cpp")
lst2=$(find . -name "*.h")

for FILE in $lst1
do
    cp $FILE $cpPath
done

for FILE in $lst2
do
    cp $FILE $cpPath
done

