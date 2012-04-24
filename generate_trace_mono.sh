#!/bin/sh -x

format_trace.exe $1 cnx_write_buffer cnx_filter2 cnx_filter1 cnx_slice2 cnx_slice1 cnx_main -cpu 0 CPU0
