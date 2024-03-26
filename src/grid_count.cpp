#include "grid_count.hpp"

void grid_count(int dim, int n_molecules, int lattice_size, int grid_size, std::vector<int> &grid, std::vector<double> &particles){
	double grid_bin_size = static_cast<double>(lattice_size) / grid_size;
	double eps = 1e-10;
	int x_bin, y_bin;
	grid.resize(grid_size*grid_size, 0);
	for (int i = 0; i < n_molecules; i++){
		int pos_x = 0, pos_y = 1;
		x_bin = std::floor((particles[i*dim + pos_x] + lattice_size/2.0) / grid_bin_size - eps);
		y_bin = std::floor((particles[i*dim + pos_y] + lattice_size/2.0) / grid_bin_size - eps);
		grid[y_bin*grid_size + x_bin] += 1;
	}
}