reset

set term pdf size 3in,3in font "Times New Roman,10"
set out ARG2

set autoscale x
set autoscale y

set xtics rotate by 90
set xtics 100000
set ytics 1

set title "{/:Bold Entropy versus time}"
set xlabel "{/:Bold time}"
set ylabel "{/:Bold Entropy}"

plot ARG1 ps 0.1 pt 7 lc "black" notitle

unset output