reset

set term pdf size 3in,3in font "Times New Roman,10"
set out ARG3

set logscale x
set logscale y

beg_1 = strstrt(ARG3, "expon")
beg_2 = strstrt(ARG3, "coeff")
end = strstrt(ARG3, ".pdf")
expon = real(substr(ARG3, beg_1+6, beg_2-2))
coeff = real(substr(ARG3, beg_2+6, end-1))

set format x "%.0tx10^{%T}"
set grid

set title "{/:Bold RMSD versus time}"
set xlabel "{/:Bold time}"
set ylabel "{/:Bold RMSD}"

set key font ",10" box

plot ARG1 t "non-stabilized" ps 0.1 pt 7 lc "black", \
	 ARG2 t "stabilized" ps 0.1 pt 7 lc "blue", \
	 coeff * x**expon t "fitted" lw 2 dt 2 lc "red"

unset output