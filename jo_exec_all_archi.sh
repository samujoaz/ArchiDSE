
#./test_cpu_exploration.exe DSE inputfile/compositionarchi.txt inputfile/composition.txt cpuloadfile 70 85
./test_cpu_exploration.exe DSE comparaison_imx/  compositionarchi_temp.txt composition_temp.txt cpuloadfile 80 90 cnx_slice1 14 cnx_slice2 8 cnx_slice3 10 cnx_slice4 12
#./test_cpu_exploration.exe DSE openpeople/  compositionarchi.txt composition.txt cpuloadfile 70 85 
#gnuplot hist_all_archi.gnu 
dot -Tps graph.dot -oh.ps
#okular h.ps


