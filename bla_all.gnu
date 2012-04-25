# file refering to specific files ...
plot  "bla_cnx_write_buffer.gnu" with lines title "cnx_write_buffer", "bla_cnx_filter2.gnu" with lines title "cnx_filter2", "bla_cnx_filter1.gnu" with lines title "cnx_filter1", "bla_cnx_slice2.gnu" with lines title "cnx_slice2", "bla_cnx_slice1.gnu" with lines title "cnx_slice1", "bla_cnx_main.gnu" with lines title "cnx_main", "bla_CPU0.gnu" with lines title "CPU0" , 7.09424 title "CPU0 (mean)", "bla_CPU1.gnu" with lines title "CPU1" , 8.35939 title "CPU1 (mean)"
set yrange[0:24]
pause -1
