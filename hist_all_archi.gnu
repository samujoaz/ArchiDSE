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
 set xtics (  "200\n" 0,  "200\n200\n" 1,  "250\n250\n" 2,  "300\n300\n" 3,  "350\n350\n" 4,  "400\n400\n" 5,  "450\n450\n" 6,  "500\n450\n" 7,  "550\n500\n" 8,  "600\n500\n" 9,  "600\n500\n" 10)
plot 'all_cpu_hist.dat' using 1 title "cpu_0", '' using 2 title "cpu_1", 85.7 with lines linecolor rgb "red"  title "Max", 70  with lines linecolor rgb "red" title "Min";
pause -1 
