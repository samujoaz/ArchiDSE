# file refering to specific files ...
plot  "cpuloadfile15/a_cnx_write_buffer.gnu" with lines title "cnx_write_buffer", "cpuloadfile15/a_CPU0.gnu" with lines title "CPU0" , 2.4898 title "CPU0 (mean)", "cpuloadfile15/a_CPU1.gnu" with lines title "CPU1" , 3.41098 title "CPU1 (mean)", "cpuloadfile15/a_CPU2.gnu" with lines title "CPU2" , 4.36478 title "CPU2 (mean)", "cpuloadfile15/a_CPU3.gnu" with lines title "CPU3" , 5.3694 title "CPU3 (mean)"
set yrange[0:15]
pause -1
