set xrange [-200:200]
set yrange [-200:200]

set style line 1 lc rgb 'black' pt 7 ps 0.5 lt 1 lw 2
set style line 2 lc rgb 'black' lt 0 lw 1

# Para la malla
set grid front ls 2
set xtics 20
set ytics 20

set terminal pngcairo enhanced font 'Arial,10'

# Graficar las posiciones de las partículas
set output "particles_position_t=0.png"
set title "Cream in Coffee t=0"
plot "cream_in_coffee_particles_t0.txt" using 1:2 with points ls 1 notitle

unset output