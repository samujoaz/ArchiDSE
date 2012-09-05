
#./test_cpu_exploration.exe DSE inputfile/compositionarchi.txt inputfile/composition.txt cpuloadfile 70 85
./test_cpu_exploration.exe DSE imx/  compositionarchi.txt composition.txt cpuloadfile 70 85
#gnuplot hist_all_archi.gnu 
dot -Tps graph.dot -oh.ps
#okular h.ps


