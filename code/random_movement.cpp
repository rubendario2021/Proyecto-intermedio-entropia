#include "random_movement.hpp"

void random_movement(int &dim, int &n_molecules, int &lattice_size, std::vector<double> &molecules, std::mt19937 &gen, std::uniform_int_distribution<int> &direction_distribution, int &problem_id, int &count_out){

    // The constant movement passage of the simulation is defined
    double step_size = 0.005;

    // Definition of constants for particle movement
    int pos_x = 0, pos_y = 1;
    int direction = 0;
    double limit = lattice_size/2.0; // Limit for a centered coordinate system
    double m_limit = -1.0*limit;

    // Definition of constants for the hole in the wall
	double hole = lattice_size/10.0;
    double out = 2.0*lattice_size;

    // For contact with the wall or position outside the box, the movement in that direction is reflected twice
    double step_backward = 2.0*step_size; 

    for (int i = 0; i < n_molecules; i++){
        direction = direction_distribution(gen);
        
        //If the molecule is outside the container, then it should ignore the movement
		if ((problem_id == 4) && (molecules[i*dim + pos_x] == out)) { direction = 4;}

        switch (direction) {
            case 0: // Up
                molecules[i*dim + pos_y] += step_size;
                if (molecules[i*dim + pos_y] >= limit) molecules[i*dim + pos_y] -= step_backward;
                break;

            case 1: // Down
                molecules[i*dim + pos_y] -= step_size;
                if (molecules[i*dim + pos_y] <= m_limit) {
					molecules[i*dim + pos_y] += step_backward;
                    //For problem 4, if the position in x is within 1/5 of the container's side value, then the molecule is removed
					if ((problem_id == 4) && (std::fabs(molecules[i*dim + pos_x]) < hole)) {
						molecules[i*dim + pos_x] = out;
						count_out++;
					} 
				}
				break;

            case 2: // Left
                molecules[i*dim + pos_x] -= step_size;
                if (molecules[i*dim + pos_x] <= m_limit) molecules[i*dim + pos_x] += step_backward;
                break;

            case 3: // Right
                molecules[i*dim + pos_x] += step_size;
                if (molecules[i*dim + pos_x] >= limit) molecules[i*dim + pos_x] -= step_backward;
                break;

			default:
				break;
        }
    }   
}