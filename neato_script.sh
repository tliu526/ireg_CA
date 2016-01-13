#!/bin/bash

# Usage is:
# neato_script <dot file name> <number of files>
for i in `seq 0 $2`;
do
    neato -Tjpg -o $1_$i.jpg $1_$i.dot
done