#!/bin/sh

[ x$BENCH_ROOT = "x" ] && echo please set BENCH_ROOT env var && exit
$BENCH_ROOT/generators/component_generator.exe main_cpu_0.txt
$BENCH_ROOT/generators/component_generator.exe slice_cpu_1.txt
$BENCH_ROOT/generators/component_generator.exe slice_cpu_1.txt
$BENCH_ROOT/generators/component_generator.exe slice_cpu_1.txt
$BENCH_ROOT/generators/component_generator.exe slice_cpu_2.txt
$BENCH_ROOT/generators/component_generator.exe slice_cpu_2.txt
$BENCH_ROOT/generators/component_generator.exe slice_cpu_2.txt
$BENCH_ROOT/generators/component_generator.exe slice_cpu_2.txt
$BENCH_ROOT/generators/component_generator.exe slice_cpu_2.txt
$BENCH_ROOT/generators/component_generator.exe slice_cpu_2.txt
$BENCH_ROOT/generators/component_generator.exe filter_cpu_1.txt
$BENCH_ROOT/generators/component_generator.exe filter_cpu_3.txt
$BENCH_ROOT/generators/component_generator.exe filter_cpu_3.txt
$BENCH_ROOT/generators/component_generator.exe filter_cpu_3.txt
$BENCH_ROOT/generators/component_generator.exe filter_cpu_3.txt
$BENCH_ROOT/generators/component_generator.exe filter_cpu_4.txt
$BENCH_ROOT/generators/component_generator.exe filter_cpu_0.txt
$BENCH_ROOT/generators/component_generator.exe filter_cpu_0.txt
$BENCH_ROOT/generators/component_generator.exe filter_cpu_0.txt
$BENCH_ROOT/generators/component_generator.exe write_buffer_cpu_0.txt
OS_NAME=`uname`
COMPILE_OPTS=""
LIBLINK=""
[ $OS_NAME = "Linux" ] && COMPILE_OPTS="-pthread" && LIBLINK="-lrt"
${CROSS_PREFIX}g++ $COMPILE_OPTS -c -I $BENCH_ROOT/runtime -I . main_behaviour_cpu_0.cpp
${CROSS_PREFIX}g++ $COMPILE_OPTS -c -I $BENCH_ROOT/runtime -I . slice_behaviour_cpu_1.cpp
${CROSS_PREFIX}g++ $COMPILE_OPTS -c -I $BENCH_ROOT/runtime -I . slice_behaviour_cpu_1.cpp
${CROSS_PREFIX}g++ $COMPILE_OPTS -c -I $BENCH_ROOT/runtime -I . slice_behaviour_cpu_1.cpp
${CROSS_PREFIX}g++ $COMPILE_OPTS -c -I $BENCH_ROOT/runtime -I . slice_behaviour_cpu_2.cpp
${CROSS_PREFIX}g++ $COMPILE_OPTS -c -I $BENCH_ROOT/runtime -I . slice_behaviour_cpu_2.cpp
${CROSS_PREFIX}g++ $COMPILE_OPTS -c -I $BENCH_ROOT/runtime -I . slice_behaviour_cpu_2.cpp
${CROSS_PREFIX}g++ $COMPILE_OPTS -c -I $BENCH_ROOT/runtime -I . slice_behaviour_cpu_2.cpp
${CROSS_PREFIX}g++ $COMPILE_OPTS -c -I $BENCH_ROOT/runtime -I . slice_behaviour_cpu_2.cpp
${CROSS_PREFIX}g++ $COMPILE_OPTS -c -I $BENCH_ROOT/runtime -I . slice_behaviour_cpu_2.cpp
${CROSS_PREFIX}g++ $COMPILE_OPTS -c -I $BENCH_ROOT/runtime -I . filter_behaviour_cpu_1.cpp
${CROSS_PREFIX}g++ $COMPILE_OPTS -c -I $BENCH_ROOT/runtime -I . filter_behaviour_cpu_3.cpp
${CROSS_PREFIX}g++ $COMPILE_OPTS -c -I $BENCH_ROOT/runtime -I . filter_behaviour_cpu_3.cpp
${CROSS_PREFIX}g++ $COMPILE_OPTS -c -I $BENCH_ROOT/runtime -I . filter_behaviour_cpu_3.cpp
${CROSS_PREFIX}g++ $COMPILE_OPTS -c -I $BENCH_ROOT/runtime -I . filter_behaviour_cpu_3.cpp
${CROSS_PREFIX}g++ $COMPILE_OPTS -c -I $BENCH_ROOT/runtime -I . filter_behaviour_cpu_4.cpp
${CROSS_PREFIX}g++ $COMPILE_OPTS -c -I $BENCH_ROOT/runtime -I . filter_behaviour_cpu_0.cpp
${CROSS_PREFIX}g++ $COMPILE_OPTS -c -I $BENCH_ROOT/runtime -I . filter_behaviour_cpu_0.cpp
${CROSS_PREFIX}g++ $COMPILE_OPTS -c -I $BENCH_ROOT/runtime -I . filter_behaviour_cpu_0.cpp
${CROSS_PREFIX}g++ $COMPILE_OPTS -c -I $BENCH_ROOT/runtime -I . write_buffer_behaviour_cpu_0.cpp
${CROSS_PREFIX}g++ test.cpp $COMPILE_OPTS -I $BENCH_ROOT/runtime -I . filter_behaviour_cpu_0.o filter_behaviour_cpu_1.o filter_behaviour_cpu_3.o filter_behaviour_cpu_4.o main_behaviour_cpu_0.o slice_behaviour_cpu_1.o slice_behaviour_cpu_2.o write_buffer_behaviour_cpu_0.o -L $BENCH_ROOT/runtime -lruntime $LIBLINK -o test.exe
