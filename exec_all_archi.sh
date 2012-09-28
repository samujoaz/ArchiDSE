
#./test_cpu_exploration.exe DSE inputfile/compositionarchi.txt inputfile/composition.txt cpuloadfile 70 85
#./test_cpu_exploration.exe DSE comparaison_imx/  compositionarchi4.txt composition_filter4.txt cpuloadfile 80 90
#cnx_slice1 10 cnx_slice2 10  

#./test_cpu_exploration.exe DSE comparaison_imx/  compositionarchi2.txt composition_filter2.txt cpuloadfile 80 90 cnx_slice1 20 cnx_slice2 20 
./test_cpu_exploration.exe DSE inputfile3/  compositionarchi.txt composition.txt  cpuloadfile 70 80 cnx_slice1 15 cnx_slice2 15 cnx_filter1 15 cnx_filter2 15 cnx_slice3 15 cnx_filter3 15 cnx_slice4 15 cnx_filter4 10 cnx_slice5 10 cnx_filter5 10 cnx_slice6 10 cnx_filter6 15 cnx_slice7 10 cnx_filter7 10 cnx_slice8 10 cnx_filter8 10



#gnuplot hist_all_archi.gnu 
dot -Tps graph.dot -oh.ps
#okular h.ps


