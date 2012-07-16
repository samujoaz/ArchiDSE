# file refering to specific files ...
plot  "cpuloadfile14/a_cnx_write_buffer.gnu" with lines title "cnx_write_buffer", "cpuloadfile14/a_CPU0.gnu" with lines title "CPU0" , 2.48967 title "CPU0 (mean)", "cpuloadfile14/a_CPU1.gnu" with lines title "CPU1" , 3.41187 title "CPU1 (mean)", "cpuloadfile14/a_CPU2.gnu" with lines title "CPU2" , 4.36414 title "CPU2 (mean)", "cpuloadfile14/a_CPU3.gnu" with lines title "CPU3" , 5.36418 title "CPU3 (mean)"
set yrange[0:15]
pause -1
