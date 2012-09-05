
set style function lines
set size 1.0, 1.0

set multiplot

set grid

unset key
  
#  Plot duration connection*******************************************
set size 1,0.5
set origin 0.0,0.0
set yrange [0:100]
set xrange [-1:25]
set style histogram cluster gap 4
set style fill solid border -1
set boxwidth 1.0
#set title "Second Order System Transfer Function - Phase"
#set label 1 ""
set ylabel "duree connection" #at -1,-1 rotate by 0   offset character 0,-0.5, 0


plot  'cnx_slice1.dat' with lines ,  14 with lines title "Max_cnx_slice1", 'cnx_slice2.dat' with lines ,  8 with lines title "Max_cnx_slice2", 'cnx_slice3.dat' with lines ,  10 with lines title "Max_cnx_slice3", 'cnx_slice4.dat' with lines ,  12 with lines title "Max_cnx_slice4"

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
set xtics  norangelimit font ",9"
 set xtics (  "200\n" 0,  "200\n200\n200\n200\n" 1,  "150\n150\n150\n150\n" 2,  "175\n175\n175\n175\n" 3,  "200\n200\n200\n200\n" 4,  "225\n225\n225\n225\n" 5,  "250\n250\n250\n250\n" 6,  "275\n275\n275\n275\n" 7,  "300\n300\n300\n300\n" 8,  "325\n325\n325\n325\n" 9,  "350\n350\n350\n350\n" 10,  "375\n375\n375\n375\n" 11,  "400\n400\n400\n400\n" 12,  "425\n425\n425\n425\n" 13,  "450\n450\n450\n450\n" 14,  "475\n475\n475\n475\n" 15,  "500\n500\n500\n500\n" 16,  "525\n525\n525\n525\n" 17,  "550\n550\n550\n550\n" 18,  "575\n575\n575\n575\n" 19,  "600\n600\n600\n600\n" 20,  "625\n625\n625\n625\n" 21,  "650\n650\n650\n650\n" 22,  "675\n675\n675\n675\n" 23,  "700\n700\n700\n700\n" 24,  "725\n725\n725\n725\n" 25,  "750\n750\n750\n750\n" 26,  "775\n775\n775\n775\n" 27,  "800\n775\n775\n800\n" 28,  "800\n775\n775\n800\n" 29)
plot 'all_cpu_hist.dat' using 1 title "cpu_0", '' using 2 title "cpu_1", '' using 3 title "cpu_2", '' using 4 title "cpu_3", 85 with lines linecolor rgb "red"  title "Max", 70  with lines linecolor rgb "red" title "Min";

  

unset multiplot
pause -1;
pause -1;