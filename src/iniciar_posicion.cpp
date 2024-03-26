#include "iniciar_posicion.hpp"

void iniciar_posicion(int dim, int n_molecules, std::vector<double> &particles){
    double separacion = 0.01;
    int lado_cuadrado = std::sqrt(n_molecules);

    for (int i = 0; i < n_molecules; i = i + 1){
		int pos_x = 0, pos_y = 1;
		particles[i*dim + pos_x] = (i % lado_cuadrado)*separacion;
        particles[i*dim + pos_y] = floor(i/lado_cuadrado)*separacion;
	}
}