# file refering to specific files ...
plot  "cpuloadfile1/a_CPU0.gnu" with lines title "CPU0", "cpuloadfile1/a_CPU1.gnu" with lines title "CPU1", "cpuloadfile1/a_CPU2.gnu" with lines title "CPU2", "cpuloadfile1/a_CPU3.gnu" with lines title "CPU3"
set yrange[0:15]
pause -1
