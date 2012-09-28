#!/bin/sh -x
#cd ../../bench_generator_JO/
#chmod 755 source_me.sh
#./source_me.sh
#cd -

composite_generator.exe composition.txt test.cpp
chmod 755 build.sh
./build.sh
sudo ./test.exe 2> $1

#./trace.exe  $1 cnx_write_buffer cnx_filter2 cnx_filter1 cnx_slice2 cnx_slice1 cnx_main -cpu 0 CPU0 1 CPU1
./trace.exe $1 $2 $3
#./trace.exe $1 cnx_write_buffer cnx_filter2 cnx_filter1 cnx_slice2 cnx_slice1 cnx_main -cpu 0 CPU0 1 CPU1 $i

#gnuplot cpuloadfile$2/$1_all.gnu &
#dot -Tps graph.dot -o graph.ps
cp a cpuloadfile$3
cp graph.dot cpuloadfile$3
#cp slice_1.txt cpuloadfile$3
#cp slice_2.txt cpuloadfile$3
#cp slice_3.txt cpuloadfile$3
#cp slice_4.txt cpuloadfile$3
#okular graph.ps & 
