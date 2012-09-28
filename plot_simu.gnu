
set style function lines
set size 1.0, 1.0

set multiplot

set grid

unset key
  
#  Plot duration connection*******************************************
set size 1,0.5
set origin 0.0,0.0
set yrange [0:100]
set xrange [0:30]
set style histogram cluster gap 4
set style fill solid border -1
set boxwidth 1.0
#set title "Second Order System Transfer Function - Phase"


set ylabel "duree connection" 


plot   'cnx_slice1.dat' with linespoints ,  16 with lines title "Max_cnx_slice1",  'cnx_slice2.dat' with linespoints ,  18 with lines title "Max_cnx_slice2",  'cnx_filter1.dat' with linespoints ,  20 with lines title "Max_cnx_filter1",  'cnx_filter2.dat' with linespoints ,  22 with lines title "Max_cnx_filter2";

#  Plot Histogramme *********************************************************
set size 1,0.5
set origin 0.0, 0.5
set yrange [0:100]
set xrange [-1:30]
set ylabel "Taux de chargement des CPU (%)"
set label "Frequence\n (MHz)"  at -1,-1 rotate by 0   offset character 0,-0.5, 0
set style data histogram
set style histogram cluster gap 4
set style fill solid border -1
set boxwidth 1.0
set xtics border in scale 0,0 nomirror rotate by 90  offset character 1.7,-1, 0
set xtics  norangelimit font ",7"
 set xtics (  "500\n" 0,  "500\n300\n300\n" 1,  "500\n250\n250\n" 2,  "500\n200\n200\n" 3,  "500\n175\n175\n" 4,  "525\n225\n200\n" 5,  "550\n275\n225\n" 6,  "575\n325\n250\n" 7,  "600\n375\n275\n" 8,  "625\n425\n300\n" 9,  "650\n475\n325\n" 10,  "675\n525\n350\n" 11,  "700\n575\n375\n" 12,  "725\n625\n400\n" 13,  "750\n675\n425\n" 14,  "775\n725\n450\n" 15,  "800\n750\n475\n" 16)
plot 'all_cpu_hist.dat' using 1 title "cpu_0", '' using 2 title "cpu_1", '' using 3 title "cpu_2", 85 with lines linecolor rgb "red"  title "Max", 70  with lines linecolor rgb "red" title "Min";


unset multiplot
pause -1;