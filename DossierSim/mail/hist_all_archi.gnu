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
 set xtics (  "200\n" 0,  "200\n200\n200\n200\n" 1,  "200\n200\n200\n200\n" 2,  "175\n300\n300\n150\n" 3,  "275\n400\n400\n100\n" 4,  "375\n500\n500\n150\n" 5,  "475\n600\n500\n250\n" 6,  "575\n600\n500\n350\n" 7,  "550\n600\n500\n400\n" 8,  "575\n625\n525\n425\n" 9)
plot 'all_cpu_hist.dat' using 1 title "cpu_0", '' using 2 title "cpu_1", '' using 3 title "cpu_2", '' using 4 title "cpu_3", 90 with lines linecolor rgb "red"  title "Max", 80  with lines linecolor rgb "red" title "Min";
pause -1 
