# file refering to specific files ...
plot  "cpuloadfile4/a_cnx_write_buffer.gnu" with lines title "cnx_write_buffer", "cpuloadfile4/a_CPU0.gnu" with lines title "CPU0" , 2.48948 title "CPU0 (mean)", "cpuloadfile4/a_CPU1.gnu" with lines title "CPU1" , 3.16356 title "CPU1 (mean)", "cpuloadfile4/a_CPU2.gnu" with lines title "CPU2" , 0 title "CPU2 (mean)", "cpuloadfile4/a_CPU3.gnu" with lines title "CPU3" , 0 title "CPU3 (mean)"
set yrange[0:15]
pause -1
