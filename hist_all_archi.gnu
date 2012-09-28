reset
set yrange [0:100]
set xrange [-1:]
set ylabel "Taux de chargement des CPU (%)"
set label "Frequence\n (MHz)"  at -1,-1 rotate by 0   offset character 0,-0.5, 0
set style data histogram
set style histogram cluster gap 4 
set style fill solid border -1
set boxwidth 1.0 
set xtics border in scale 0,0 nomirror rotate by 90  offset character 1.7,-1, 0
set xtics  norangelimit font ",9"
 set xtics (  "500\n" 0,  "500\n500\n500\n500\n500\n500\n500\n500\n" 1,  "500\n500\n500\n500\n500\n500\n500\n500\n" 2,  "600\n600\n600\n600\n600\n600\n600\n450\n" 3,  "600\n700\n700\n700\n700\n600\n600\n400\n" 4,  "600\n800\n800\n800\n800\n600\n600\n350\n" 5,  "600\n850\n850\n900\n900\n600\n600\n300\n" 6,  "600\n850\n850\n900\n900\n600\n600\n250\n" 7,  "600\n850\n850\n900\n900\n600\n600\n200\n" 8,  "650\n875\n875\n925\n900\n650\n650\n200\n" 9,  "700\n900\n900\n950\n900\n700\n700\n200\n" 10,  "750\n925\n925\n975\n900\n750\n750\n200\n" 11,  "800\n950\n950\n1000\n900\n800\n800\n200\n" 12,  "800\n950\n950\n1000\n900\n800\n800\n200\n" 13)
plot 'all_cpu_hist.dat' using 1 title "cpu_0", '' using 2 title "cpu_1", '' using 3 title "cpu_2", '' using 4 title "cpu_3", '' using 5 title "cpu_4", '' using 6 title "cpu_5", '' using 7 title "cpu_6", '' using 8 title "cpu_7", 80 with lines linecolor rgb "red"  title "Max", 70  with lines linecolor rgb "red" title "Min";
pause -1 
