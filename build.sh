#!/bin/sh

[ x$BENCH_ROOT = "x" ] && echo please set BENCH_ROOT env var && exit
$BENCH_ROOT/generators/component_generator.exe main_0.txt
$BENCH_ROOT/generators/component_generator.exe slice_1.txt
$BENCH_ROOT/generators/component_generator.exe slice_2.txt
$BENCH_ROOT/generators/component_generator.exe filter_1.txt
$BENCH_ROOT/generators/component_generator.exe filter_2.txt
$BENCH_ROOT/generators/component_generator.exe write_buffer_0.txt
$BENCH_ROOT/generators/component_generator.exe generator_0.txt
$BENCH_ROOT/generators/component_generator.exe cypher_0.txt
$BENCH_ROOT/generators/component_generator.exe coder_0.txt
$BENCH_ROOT/generators/component_generator.exe modulator_0.txt
$BENCH_ROOT/generators/component_generator.exe snk_0.txt
OS_NAME=`uname`
COMPILE_OPTS=""
LIBLINK=""
[ $OS_NAME = "Linux" ] && COMPILE_OPTS="-pthread" && LIBLINK="-lrt"
${CROSS_PREFIX}g++ $COMPILE_OPTS -c -I $BENCH_ROOT/runtime -I . main_behaviour_0.cpp
${CROSS_PREFIX}g++ $COMPILE_OPTS -c -I $BENCH_ROOT/runtime -I . slice_behaviour_1.cpp
${CROSS_PREFIX}g++ $COMPILE_OPTS -c -I $BENCH_ROOT/runtime -I . slice_behaviour_2.cpp
${CROSS_PREFIX}g++ $COMPILE_OPTS -c -I $BENCH_ROOT/runtime -I . filter_behaviour_1.cpp
${CROSS_PREFIX}g++ $COMPILE_OPTS -c -I $BENCH_ROOT/runtime -I . filter_behaviour_2.cpp
${CROSS_PREFIX}g++ $COMPILE_OPTS -c -I $BENCH_ROOT/runtime -I . write_buffer_behaviour_0.cpp
${CROSS_PREFIX}g++ $COMPILE_OPTS -c -I $BENCH_ROOT/runtime -I . generator_behaviour_0.cpp
${CROSS_PREFIX}g++ $COMPILE_OPTS -c -I $BENCH_ROOT/runtime -I . cypher_behaviour_0.cpp
${CROSS_PREFIX}g++ $COMPILE_OPTS -c -I $BENCH_ROOT/runtime -I . coder_behaviour_0.cpp
${CROSS_PREFIX}g++ $COMPILE_OPTS -c -I $BENCH_ROOT/runtime -I . modulator_behaviour_0.cpp
${CROSS_PREFIX}g++ $COMPILE_OPTS -c -I $BENCH_ROOT/runtime -I . snk_behaviour_0.cpp
${CROSS_PREFIX}g++ test.cpp $COMPILE_OPTS -I $BENCH_ROOT/runtime -I . coder_behaviour_0.o cypher_behaviour_0.o filter_behaviour_1.o filter_behaviour_2.o generator_behaviour_0.o main_behaviour_0.o modulator_behaviour_0.o slice_behaviour_1.o slice_behaviour_2.o snk_behaviour_0.o write_buffer_behaviour_0.o -L $BENCH_ROOT/runtime -lruntime $LIBLINK -o test.exe
