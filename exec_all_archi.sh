
#./test_cpu_exploration.exe DSE inputfile/compositionarchi.txt inputfile/composition.txt cpuloadfile 70 85
./test_cpu_exploration.exe DSE inputfile2/  compositionarchi.txt composition.txt cpuloadfile 70 85 cnx_slice1 15 cnx_slice2 15 cnx_filter1 15 cnx_filter2 15 
#gnuplot hist_all_archi.gnu 
dot -Tps graph.dot -oh.ps
#okular h.ps


