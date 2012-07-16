# file refering to specific files ...
plot  "cpuloadfile10/a_CPU0.gnu" with lines title "CPU0", "cpuloadfile10/a_CPU1.gnu" with lines title "CPU1", "cpuloadfile10/a_CPU2.gnu" with lines title "CPU2", "cpuloadfile10/a_CPU3.gnu" with lines title "CPU3"
set yrange[0:15]
pause -1
