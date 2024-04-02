reset

set term pdf size 3in,3in font "Times New Roman,10"
set out ARG2

set logscale x
set logscale y

beg_1 = strstrt(ARG2, "expon")
beg_2 = strstrt(ARG2, "coeff")
end = strstrt(ARG2, ".pdf")
expon = real(substr(ARG2, beg_1+6, beg_2-2))
coeff = real(substr(ARG2, beg_2+6, end-1))

set format x "%.0tx10^{%T}"
set grid

set title "{/:Bold RMSD versus time}"
set xlabel "{/:Bold time}"
set ylabel "{/:Bold RMSD}"

set key font ",10" box
set key bottom right

plot ARG1 t "simulated" ps 0.1 pt 7 lc "black", \
	 coeff * x**expon t "fitted" dashtype 2 lc "red"

unset output