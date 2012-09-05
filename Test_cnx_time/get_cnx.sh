#!/bin/sh -x

./trace.exe  $1 cnx_main  cnx_write_buffer cnx_filter2 cnx_filter1 cnx_slice2 cnx_slice1 -cpu 0 CPU0 1 CPU1
