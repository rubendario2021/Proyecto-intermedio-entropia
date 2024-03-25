#include "entropy_val.hpp"
#include <iostream>

double entropy_val(int dim, int n_molecules, int lattice_size, int grid_size, std::vector<int> &grid_count, std::vector<double> &particles){
	double entropy;
	double grid_bin_size = (float)(lattice_size) / (grid_size - 1);
	std::cout << grid_bin_size << "\n";
	double x_bin, y_bin;
	for (int i = 0; i < n_molecules; i++){
		int pos_x = 0, pos_y = 1;
		x_bin = std::floor((particles[i*dim + pos_x] + lattice_size/2.0)/grid_bin_size);
		y_bin = std::floor((particles[i*dim + pos_y] + lattice_size/2.0)/grid_bin_size);
		grid_count[y_bin*grid_size + x_bin] += 1;
	}
	return entropy;
}