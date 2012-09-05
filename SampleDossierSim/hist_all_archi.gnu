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
 set xtics (  "200\n" 0,  "200\n" 1,  "200\n" 2,  "250\n" 3,  "300\n" 4,  "350\n" 5,  "400\n" 6,  "450\n" 7,  "500\n" 8,  "550\n" 9,  "600\n" 10,  "650\n" 11,  "700\n" 12,  "750\n" 13,  "800\n" 14)
plot 'all_cpu_hist.dat' using 1 title "cpu_0", 85 with lines linecolor rgb "red"  title "Max", 70  with lines linecolor rgb "red" title "Min";
pause -1 
