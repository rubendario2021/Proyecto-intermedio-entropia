#include "grid_count.hpp"

void grid_count(int &dim, int &n_molecules, int &lattice_size, int &grid_size, std::vector<int> &grid, std::vector<double> &molecules){
	// Definition of the size of each cell's side in the grid
	double grid_bin_size = static_cast<double>(lattice_size) / grid_size;

	int x_bin = 0, y_bin = 0;
	int pos_x = 0, pos_y = 1;
	double min_val = -lattice_size/2.0;
	
	// The counter for storing the quantity of molecules is reset
	grid.clear();
	grid.resize(grid_size*grid_size, 0);

	for (int i = 0; i < n_molecules; i++){
		/* A program useful in a domain with particles in x,y = [-10,10). The grid index is obtained as: 
				Index = distance from the left/bottom edge / Grid cell size */
		x_bin = static_cast<int>((molecules[i*dim + pos_x] - min_val) / grid_bin_size);
		y_bin = static_cast<int>((molecules[i*dim + pos_y] - min_val) / grid_bin_size);
		grid[y_bin*grid_size + x_bin] += 1; //
	}
}