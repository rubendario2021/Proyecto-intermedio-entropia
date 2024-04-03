reset

set term pdf size 3in,3in font "Times New Roman,10"
set out ARG2

set autoscale x
set logscale y

set format y "%.0tx10^{%T}"

set grid

set title "{/:Bold Computing time vs lattice size}"
set xlabel "{/:Bold Lattice size}"
set ylabel "{/:Bold Computing time [ms]}"

plot ARG1 with lines lc "black" notitle, \
     ARG1 with points pt 7 ps 0.4 lc "red" notitle

unset output