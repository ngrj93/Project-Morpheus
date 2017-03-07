set title "Hit/Miss Live Graph" 
set xlabel "Time (s)"
set term x11 1 noraise
set ylabel "Hit and Miss Count"
set yrange [-5:11]
plot "/home/nagaraj/hits.dat" with linespoints
pause 1
reread
