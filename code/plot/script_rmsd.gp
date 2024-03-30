reset

set term pdf size 3in,3in font "Times New Roman,10"
set out ARG2

set autoscale x
set autoscale y

set format x "%.0tx10^{%T}"
set xtics 1e6
set ytics 1
set grid

set title "{/:Bold RMSQ versus time}"
set xlabel "{/:Bold time}"
set ylabel "{/:Bold RMSQ}"

plot ARG1 ps 0.05 pt 7 lc "black" notitle

unset output