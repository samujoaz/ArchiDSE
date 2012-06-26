reset
set yrange [0:100]
set xrange [-1:]
set ylabel "Taux de chargement des CPU (%)"
set label "Frequence\n (MHz)"  at -1,-1 rotate by 0   offset character 0,-0.5, 0
set style data histogram
set style histogram cluster gap 10
set style fill solid border -1
set boxwidth 1.0 
set xtics border in scale 0,0 nomirror rotate by 90  offset character 1.7,-1, 0
set xtics  norangelimit font ",9"
 set xtics (  "150\n150\n150\n150\n150\n" 0,  "150\n150\n150\n150\n150\n150\n" 1,  "150\n225\n225\n225\n225\n150\n" 2,  "225\n300\n300\n300\n300\n150\n" 3,  "300\n325\n325\n325\n325\n150\n" 4,  "325\n350\n350\n350\n350\n150\n" 5,  "350\n375\n375\n375\n375\n150\n" 6,  "350\n375\n425\n425\n425\n150\n" 7,  "350\n375\n425\n475\n475\n150\n" 8,  "350\n375\n425\n525\n475\n150\n" 9)
plot 'all_cpu_hist.dat' using 1 title "cpu_0", '' using 2 title "cpu_1", '' using 3 title "cpu_2", '' using 4 title "cpu_3", '' using 5 title "cpu_4", '' using 6 title "cpu_5", 85 with lines linecolor rgb "red"  title "Max", 70  with lines linecolor rgb "red" title "Min";
pause -1 
