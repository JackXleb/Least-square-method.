set title 'Experimental Data'
set xlabel 's'
set ylabel 'V'
plot 'data.txt' with linespoints title 'Experimental Data', \
     0.188881*x + 1.20465 title 'Regression Line', \
     x**0.295159*exp(-2.48616e-09*x) title 'Fitted Curve'
pause -1 'Press any key to exit'
