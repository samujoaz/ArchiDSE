# file refering to specific files ...
plot  "cpuloadfile0/a_CPU0.gnu" with lines title "CPU0", "cpuloadfile0/a_CPU1.gnu" with lines title "CPU1", "cpuloadfile0/a_CPU2.gnu" with lines title "CPU2", "cpuloadfile0/a_CPU3.gnu" with lines title "CPU3", "cpuloadfile0/a_CPU4.gnu" with lines title "CPU4"
set yrange[0:18]
pause -1
