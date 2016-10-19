#!/bin/sh

NAMES="TriangleDiffMax TriangleDiffMin TriangleSumMax TriangleSumMin" 

for file in $NAMES 
do
	c++ -Wall -o $file ${file}.cpp
	mv $file ~/bin
done
