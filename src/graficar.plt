set xrange [-10:10]
set yrange [-10:10]

set style line 1 lc rgb 'black' pt 7 ps 0.5 lt 1 lw 2
set style line 2 lc rgb 'black' lt 0 lw 1

# Para la malla
set grid front ls 2
set xtics 1
set ytics 1

set terminal pngcairo enhanced font 'Arial,10'

# Graficar las posiciones de las partículas
set output "output/Posicion_salida.png"
set title "Cream in Coffee t=t_final"
plot "output/data.txt" using 1:2 with points ls 1 notitle

unset output