# file refering to specific files ...
plot  "out_cnx_write_buffer.gnu" with lines title "cnx_write_buffer", "out_cnx_filter2.gnu" with lines title "cnx_filter2", "out_cnx_filter1.gnu" with lines title "cnx_filter1", "out_cnx_slice2.gnu" with lines title "cnx_slice2", "out_cnx_slice1.gnu" with lines title "cnx_slice1", "out_cnx_main.gnu" with lines title "cnx_main", "out_CPU0.gnu" with lines title "CPU0" , 7.0976 title "CPU0 (mean)"
set yrange[0:21]
pause -1
