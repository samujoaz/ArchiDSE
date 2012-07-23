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
 set xtics (  "150\n" 0,  "150\n150\n150\n150\n" 1,  "150\n225\n225\n150\n" 2,  "150\n225\n225\n150\n" 3,  "150\n250\n250\n150\n" 4,  "150\n250\n250\n150\n" 5,  "150\n250\n250\n150\n" 6,  "150\n250\n250\n150\n" 7,  "150\n250\n250\n150\n" 8,  "150\n250\n250\n150\n" 9,  "150\n250\n250\n150\n" 10,  "150\n250\n250\n150\n" 11,  "200\n225\n225\n125\n" 12,  "250\n275\n200\n100\n" 13,  "225\n325\n250\n100\n" 14,  "225\n375\n225\n150\n" 15,  "225\n425\n275\n125\n" 16,  "225\n475\n325\n100\n" 17,  "225\n475\n375\n100\n" 18,  "225\n525\n425\n150\n" 19,  "225\n525\n475\n125\n" 20,  "225\n525\n475\n100\n" 21,  "225\n525\n475\n100\n" 22)
plot 'all_cpu_hist.dat' using 1 title "cpu_0", '' using 2 title "cpu_1", '' using 3 title "cpu_2", '' using 4 title "cpu_3", 85 with lines linecolor rgb "red"  title "Max", 70  with lines linecolor rgb "red" title "Min";
pause -1 
