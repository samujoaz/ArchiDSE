# file refering to specific files ...
plot  "ooo_cnx_write_buffer.gnu" with lines title "cnx_write_buffer", "ooo_cnx_filter2.gnu" with lines title "cnx_filter2", "ooo_cnx_filter1.gnu" with lines title "cnx_filter1", "ooo_cnx_slice2.gnu" with lines title "cnx_slice2", "ooo_cnx_slice1.gnu" with lines title "cnx_slice1", "ooo_cnx_main.gnu" with lines title "cnx_main", "ooo_CPU0.gnu" with lines title "CPU0" , 7.04237 title "CPU0 (mean)"
set yrange[0:21]
pause -1