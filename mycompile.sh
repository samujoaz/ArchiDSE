#!/bin/sh -x

composite_generator.exe composition.txt test.cpp
chmod 755 build.sh
./build.sh
dot -Tps graph_archi.dot -o graph.ps
#okular graph.ps 
