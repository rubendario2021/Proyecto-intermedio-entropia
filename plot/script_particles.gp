reset

set term pdf {fname "Times New Roman, 10"}
set out output_file

set xrange [-10:10]
set yrange [-10:10]
set grid front ls 2
set xtics 2 
set ytics 2

# plot_name = sprintf("{/:Cream in Coffee t = }")
set title "{/:Cream in Coffee}"
set xlabel "x"
set ylabel "y"

plot input_file

unset output
