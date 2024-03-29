#include "random_movement.hpp"

void random_movement(int &dim, int &n_molecules, int &lattice_size, int &seed, std::vector<double> &molecules, std::mt19937 &gen, std::uniform_int_distribution<int> &direction_distribution){

    // The constant movement passage of the simulation is defined
    double step_size = 0.1;

    // Definition of constants for particle movement
    int pos_x = 0, pos_y = 1;
    int direction;
    double limit = lattice_size/2.0; // Limit for a centered coordinate system
    double m_limit = -1.0*limit;
    // For contact with the wall or position outside the box, the movement in that direction is reflected twice
    double step_backward = 2.0*step_size; 

    for (int i = 0; i < n_molecules; i++){
        direction = direction_distribution(gen);
        switch (direction) {
            case 0: // Arriba
                molecules[i*dim + pos_y] += step_size;
                if (molecules[i*dim + pos_y] >= limit) molecules[i*dim + pos_y] -= step_backward;
                break;
            case 1: // Abajo
                molecules[i*dim + pos_y] -= step_size;
                if (molecules[i*dim + pos_y] <= m_limit) molecules[i*dim + pos_y] += step_backward;
                break;
            case 2: // Izquierda
                molecules[i*dim + pos_x] -= step_size;
                if (molecules[i*dim + pos_x] <= m_limit) molecules[i*dim + pos_x] += step_backward;
                break;
            case 3: // Derecha
                molecules[i*dim + pos_x] += step_size;
                if (molecules[i*dim + pos_x] >= limit) molecules[i*dim + pos_x] -= step_backward;
                break;
        }
    }   
}