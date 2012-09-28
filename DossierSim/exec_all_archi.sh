
#./test_cpu_exploration.exe DSE inputfile/compositionarchi.txt inputfile/composition.txt cpuloadfile 70 85
./test_cpu_exploration.exe DSE radio1/  compositionarchi.txt composition.txt cpuloadfile 80 90 cnx_slice1 15 cnx_slice2 15 cnx_filter1 15 cnx_filter2 15 cnx_cypher10111132 30 cnx_cypher1051188 30 cnx_cypher12111132 30 cnx_cypher1221118 30  cnx_coder10111132 30 cnx_coder1051188 30 cnx_coder12111132 30 cnx_coder1221118 30 

#./test_cpu_exploration.exe DSE comparaison_imx/  compositionarchi2.txt composition_nofilter2.txt cpuloadfile 80 90 cnx_slice1 20 cnx_slice2 20 
#./test_cpu_exploration.exe DSE comparaison_imx/  compositionarchi2.txt composition_filter2.txt cpuloadfile 80 90 cnx_slice1 15 cnx_slice2 15 cnx_filter1 15 cnx_filter2 15 

#gnuplot hist_all_archi.gnu 
dot -Tps graph.dot -oh.ps
#okular h.ps


