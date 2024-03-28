reset

set term pdf size 3in,3in font "Times New Roman,10"
set out ARG2

set xrange [-10:10]
set yrange [-10:10]

set xtics 2
set ytics 2

set title "{/:Bold Cream in Coffee}"
set xlabel "{/:Bold X}"
set ylabel "{/:Bold Y}"

plot ARG1 ps 0.5 pt 7 lc "black" notitle

unset output