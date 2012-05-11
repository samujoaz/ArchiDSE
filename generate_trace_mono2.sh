#!/bin/sh -x
./trace.exe $1 cnx_write_buffer cnx_filter3 cnx_filter2  cnx_filter1 cnx_slice3 cnx_slice2 cnx_slice1 cnx_main -cpu 0 CPU0 1 CPU1 2 CPU2  $2
