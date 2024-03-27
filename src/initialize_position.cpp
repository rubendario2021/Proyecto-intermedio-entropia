#include "initialize_position.hpp"

void  initialize_position(int dim, int n_molecules, std::vector<double> &particles, int lattice_size){
    // Initial separation between particles
    double separation = 0.02; 
    // The number of input nodes must be a square number
    int length_square = std::sqrt(n_molecules);
    // The initial particles is centered in the middle of the container
    double offset = (-(length_square-1)*separation)/2.0;

    int pos_x = 0, pos_y = 1; // Pos_X = Column 0 - Pos_Y = Column 1
    for (int i = 0; i < n_molecules; i++){
        // The x position is iterated within the loop
		particles[i*dim + pos_x] = (i % length_square)*separation + offset;
        // The y position is calculated through an integer division
        particles[i*dim + pos_y] = (i/length_square)*separation + offset;
        // std::cout << "Molecula " << i+1 << "\t" << particles[i*dim + pos_x] << "\t" << particles[i*dim + pos_y] << "\n" ;
    }
}

