reset

set term pdf size 3in,3in font "Times New Roman,10"
set out ARG2

set xrange [-10:10]
set yrange [-10:10]

beg = strstrt(ARG2, "t_")
end = strstrt(ARG2, ".")
n_iter = substr(ARG2, beg+2, end-1)
fmt_n_iter = sprintf("%.0e", real(n_iter))

set xtics 2
set ytics 2
set grid

set title sprintf("{/:Bold Cream in Coffee t = 10^{%s}}", fmt_n_iter[5:]) enhanced
set xlabel "{/:Bold X}"
set ylabel "{/:Bold Y}"

plot ARG1 ps 0.2 pt 7 lc "black" notitle

unset output