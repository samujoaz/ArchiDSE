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
 set xtics (  "350\n350\n350\n350\n0\n" 0,  "350\n350\n350\n350\n" 1,  "350\n350\n350\n350\n" 2,  "350\n350\n350\n350\n" 3,  "350\n350\n350\n350\n" 4,  "350\n350\n350\n350\n" 5,  "350\n450\n350\n350\n" 6,  "350\n450\n350\n350\n" 7,  "350\n450\n350\n350\n" 8,  "350\n450\n350\n350\n" 9,  "350\n450\n350\n350\n" 10,  "350\n450\n350\n350\n" 11,  "350\n450\n350\n350\n" 12,  "350\n450\n350\n350\n" 13,  "350\n450\n350\n350\n" 14,  "400\n450\n350\n350\n" 15,  "450\n450\n350\n350\n" 16)
plot 'all_cpu_hist.dat' using 1 title "cpu_0", '' using 2 title "cpu_1", '' using 3 title "cpu_2", '' using 4 title "cpu_3", 85 with lines linecolor rgb "red"  title "Max", 70  with lines linecolor rgb "red" title "Min";
pause -1 
