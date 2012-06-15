reset
set yrange [0:100]
set xrange [-1:]
set ylabel "Taux de chargement des CPU (%)"
set label "Frequence\n (MHz)"  at -1,-1 rotate by 0   offset character 0,-0.5, 0
set style data histogram
set style histogram cluster gap 4
set style fill solid border -1
set boxwidth 1.0 
set xtics border in scale 0,0 nomirror rotate by 90  offset character 1.5,-1, 0
set xtics  norangelimit font ",7.5"
 set xtics (  "200\n200\n200\n200\n200\n" 0,  "200\n200\n200\n200\n200\n" 1,  "200\n200\n200\n200\n200\n" 2,  "200\n300\n300\n300\n200\n" 3,  "300\n350\n350\n350\n200\n" 4,  "350\n350\n400\n400\n200\n" 5,  "400\n350\n450\n450\n200\n" 6,  "400\n350\n450\n450\n200\n" 7,  "450\n350\n450\n450\n200\n" 8,  "450\n350\n450\n450\n200\n" 9,  "500\n350\n450\n450\n300\n" 10,  "500\n350\n450\n450\n300\n" 11,  "500\n350\n450\n450\n350\n" 12)
plot 'all_cpu_hist.dat' using 1 title "cpu_0", '' using 2 title "cpu_1", '' using 3 title "cpu_2", '' using 4 title "cpu_3", '' using 5 title "cpu_4", 85 with lines linecolor rgb "red"  title "Max", 70 with lines linecolor rgb "red" title "Min";
pause -1 
