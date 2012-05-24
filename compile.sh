#!/bin/sh -x
#cd ../../bench_generator_JO/
#chmod 755 source_me.sh
#./source_me.sh
#cd -
#./hello.out DSE inputfile/compositionarchi.txt  inputfile/composition.txt cpuloadfile
composite_generator.exe composition.txt test.cpp
chmod 755 build.sh
./build.sh
sudo ./test.exe 2> $1
#trace.exe  $1 cnx_write_buffer cnx_filter2 cnx_filter1 cnx_slice2 cnx_slice1 cnx_main -cpu 0 CPU0 1 CPU1
chmod 755 generate_trace_mono2.sh
 #for((i=0;i<2;i++))
 #do
./generate_trace_mono2.sh $1 $2
#./trace.exe $1 cnx_write_buffer cnx_filter2 cnx_filter1 cnx_slice2 cnx_slice1 cnx_main -cpu 0 CPU0 1 CPU1 $i

#done

#gnuplot cpuloadfile$2/$1_all.gnu &
#dot -Tps graph_archi.dot -o graph.ps
#okular graph.ps & 
