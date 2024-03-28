reset

set term pdf size 3in,3in font "Times New Roman,10"
set out ARG2

set autoscale x
set autoscale y

beg = strstrt(ARG2, "gs")
end = strstrt(ARG2, ".")
grid_size = substr(ARG2, beg+3, end-1)

set format x "%.0tx10^{%T}"
set xtics 2e5
set ytics 1
set grid

set title sprintf("{/:Bold Entropy versus time. Grid size = %.0d}", real(grid_size)) enhanced
set xlabel "{/:Bold time}"
set ylabel "{/:Bold Entropy}"

plot ARG1 ps 0.1 pt 7 lc "black" notitle

unset output