reset

set term pdf size 3in,3in font "Times New Roman,10"
set out ARG2

set logscale x
set logscale y

set format x "%.0tx10^{%T}"
set format y "%.0tx10^{%T}"
set grid

set title "{/:Bold Mean Slope [Entropy] versus time}"
set xlabel "{/:Bold time}"
set ylabel "{/:Bold Mean Slope}"

plot ARG1 ps 0.05 pt 7 lc "black" notitle

unset output