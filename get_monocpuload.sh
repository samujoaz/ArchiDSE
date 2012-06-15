#!/bin/sh -x


composite_generator.exe composition.txt test.cpp
chmod 755 build.sh
./build.sh
sudo ./test.exe 2> $1

./trace.exe $1 $2 $3

#gnuplot cpuloadfile$2/$1_all.gnu &
#dot -Tps graph.dot -o graph.ps
#cp graph.dot cpuloadfile$2
#okular graph.ps & 

