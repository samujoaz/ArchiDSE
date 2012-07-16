#!/bin/sh

[ x$BENCH_ROOT = "x" ] && echo please set BENCH_ROOT env var && exit
$BENCH_ROOT/generators/component_generator.exe main_0.txt
$BENCH_ROOT/generators/component_generator.exe slice_1.txt
$BENCH_ROOT/generators/component_generator.exe slice_2.txt
$BENCH_ROOT/generators/component_generator.exe slice_3.txt
$BENCH_ROOT/generators/component_generator.exe slice_4.txt
$BENCH_ROOT/generators/component_generator.exe slice_5.txt
$BENCH_ROOT/generators/component_generator.exe slice_6.txt
$BENCH_ROOT/generators/component_generator.exe slice_7.txt
$BENCH_ROOT/generators/component_generator.exe slice_8.txt
$BENCH_ROOT/generators/component_generator.exe slice_10.txt
$BENCH_ROOT/generators/component_generator.exe filter_1.txt
$BENCH_ROOT/generators/component_generator.exe filter_2.txt
$BENCH_ROOT/generators/component_generator.exe filter_3.txt
$BENCH_ROOT/generators/component_generator.exe filter_4.txt
$BENCH_ROOT/generators/component_generator.exe filter_5.txt
$BENCH_ROOT/generators/component_generator.exe filter_6.txt
$BENCH_ROOT/generators/component_generator.exe filter_7.txt
$BENCH_ROOT/generators/component_generator.exe filter_8.txt
$BENCH_ROOT/generators/component_generator.exe filter_10.txt
$BENCH_ROOT/generators/component_generator.exe write_buffer_0.txt
OS_NAME=`uname`
COMPILE_OPTS=""
LIBLINK=""
[ $OS_NAME = "Linux" ] && COMPILE_OPTS="-pthread" && LIBLINK="-lrt"
${CROSS_PREFIX}g++ $COMPILE_OPTS -c -I $BENCH_ROOT/runtime -I . main_behaviour_0.cpp
${CROSS_PREFIX}g++ $COMPILE_OPTS -c -I $BENCH_ROOT/runtime -I . slice_behaviour_1.cpp
${CROSS_PREFIX}g++ $COMPILE_OPTS -c -I $BENCH_ROOT/runtime -I . slice_behaviour_2.cpp
${CROSS_PREFIX}g++ $COMPILE_OPTS -c -I $BENCH_ROOT/runtime -I . slice_behaviour_3.cpp
${CROSS_PREFIX}g++ $COMPILE_OPTS -c -I $BENCH_ROOT/runtime -I . slice_behaviour_4.cpp
${CROSS_PREFIX}g++ $COMPILE_OPTS -c -I $BENCH_ROOT/runtime -I . slice_behaviour_5.cpp
${CROSS_PREFIX}g++ $COMPILE_OPTS -c -I $BENCH_ROOT/runtime -I . slice_behaviour_6.cpp
${CROSS_PREFIX}g++ $COMPILE_OPTS -c -I $BENCH_ROOT/runtime -I . slice_behaviour_7.cpp
${CROSS_PREFIX}g++ $COMPILE_OPTS -c -I $BENCH_ROOT/runtime -I . slice_behaviour_8.cpp
${CROSS_PREFIX}g++ $COMPILE_OPTS -c -I $BENCH_ROOT/runtime -I . slice_behaviour_10.cpp
${CROSS_PREFIX}g++ $COMPILE_OPTS -c -I $BENCH_ROOT/runtime -I . filter_behaviour_1.cpp
${CROSS_PREFIX}g++ $COMPILE_OPTS -c -I $BENCH_ROOT/runtime -I . filter_behaviour_2.cpp
${CROSS_PREFIX}g++ $COMPILE_OPTS -c -I $BENCH_ROOT/runtime -I . filter_behaviour_3.cpp
${CROSS_PREFIX}g++ $COMPILE_OPTS -c -I $BENCH_ROOT/runtime -I . filter_behaviour_4.cpp
${CROSS_PREFIX}g++ $COMPILE_OPTS -c -I $BENCH_ROOT/runtime -I . filter_behaviour_5.cpp
${CROSS_PREFIX}g++ $COMPILE_OPTS -c -I $BENCH_ROOT/runtime -I . filter_behaviour_6.cpp
${CROSS_PREFIX}g++ $COMPILE_OPTS -c -I $BENCH_ROOT/runtime -I . filter_behaviour_7.cpp
${CROSS_PREFIX}g++ $COMPILE_OPTS -c -I $BENCH_ROOT/runtime -I . filter_behaviour_8.cpp
${CROSS_PREFIX}g++ $COMPILE_OPTS -c -I $BENCH_ROOT/runtime -I . filter_behaviour_10.cpp
${CROSS_PREFIX}g++ $COMPILE_OPTS -c -I $BENCH_ROOT/runtime -I . write_buffer_behaviour_0.cpp
${CROSS_PREFIX}g++ test.cpp $COMPILE_OPTS -I $BENCH_ROOT/runtime -I . filter_behaviour_1.o filter_behaviour_10.o filter_behaviour_2.o filter_behaviour_3.o filter_behaviour_4.o filter_behaviour_5.o filter_behaviour_6.o filter_behaviour_7.o filter_behaviour_8.o main_behaviour_0.o slice_behaviour_1.o slice_behaviour_10.o slice_behaviour_2.o slice_behaviour_3.o slice_behaviour_4.o slice_behaviour_5.o slice_behaviour_6.o slice_behaviour_7.o slice_behaviour_8.o write_buffer_behaviour_0.o -L $BENCH_ROOT/runtime -lruntime $LIBLINK -o test.exe
