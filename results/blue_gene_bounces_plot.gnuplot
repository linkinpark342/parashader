set term postscript landscape enhanced mono "DejaVu" 12

set xlabel "Number of bounces"
set ylabel "Time (s)"
set xrange [10:40]
set yrange [0:400]

set grid ytics

set output "blue_gene_bounces_plot.eps"
pl "blue_gene_bounces_plot.txt" u 1:2 lw 1 title "256 processor" w linespoints
