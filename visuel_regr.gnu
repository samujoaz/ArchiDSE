set title "COURBE DES CONSOMMATIONS" 
set xlabel "FREQUENCE EN  MHz" 
set ylabel "CONSO" 
plot [0 :800 ] [0 : 0.25]2.50828e-07*x**2  + (-7.12316e-05)*x + (0.0773535) title "Conso L2(nJ)"
replot 2.8374e-07*x**2  + (-0.000118609)*x + (0.0642206) title "Conso L1(nJ)"
replot 5.20037e-07*x**2  + (-0.000219118)*x + (0.13591) title "Conso CPU(nJ)"
replot 3.34792e-07*x**2  + (8.77392e-05)*x + (-0.00646497) title "Conso Leackage(Watts)"
pause -1
