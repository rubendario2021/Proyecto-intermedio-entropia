reset

set term pdf size 3in,3in font "Times New Roman,10"
set out ARG2

set logscale x
set logscale y

set format x "%.0tx10^{%T}"
#set xtics 1e6
set grid

set title "{/:Bold RMSD versus time}"
set xlabel "{/:Bold time}"
set ylabel "{/:Bold RMSD}"

plot ARG1 ps 0.05 pt 7 lc "black" notitle

unset output