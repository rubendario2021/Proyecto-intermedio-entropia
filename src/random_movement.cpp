#include "random_movement.hpp"

void random_movement(int &dim, int &n_molecules, int &lattice_size, int &seed, std::vector<double> &molecules, std::mt19937 &gen, std::uniform_int_distribution<int> &direction_distribution){

    // Step size
    double step_size = 0.0005;

    int pos_x = 0, pos_y = 1;
    int direction;
    for (int i = 0; i < n_molecules; i++){
        direction = direction_distribution(gen);
        switch (direction) {
            case 0: // Arriba
                molecules[i*dim + pos_y] += step_size;
                break;
            case 1: // Abajo
                molecules[i*dim + pos_y] -= step_size;
                break;
            case 2: // Izquierda
                molecules[i*dim + pos_x] -= step_size;
                break;
            case 3: // Derecha
                molecules[i*dim + pos_x] += step_size;
                break;
        }
    }   
}