reset
set yrange [0:100]
set xrange [-1:]
set ylabel "Taux de chargement des CPU (%)"
set label "Frequence\n (MHz)"  at -1,-1 rotate by 0   offset character 0,0,0
set style data histogram
set style histogram cluster gap 5
set style fill solid border 0.5
set boxwidth 1.0 
set xtics border in scale 0,0 nomirror rotate by 0  offset character 0,0, 0
set xtics  norangelimit font ",10"

plot 'mono_archi_hist.dat' using 1:xticlabels("500  500  500  500  500  500  500  500  ") title "cpu_0", '' using 2 title "cpu_1", '' using 3 title "cpu_2", '' using 4 title "cpu_3", '' using 5 title "cpu_4", '' using 6 title "cpu_5", '' using 7 title "cpu_6", '' using 8 title "cpu_7", 85 with lines linecolor rgb "red"  title "Max", 70  with lines linecolor rgb "red" title "Min";
pause -1 
