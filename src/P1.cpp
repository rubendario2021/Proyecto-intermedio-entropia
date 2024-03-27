#include "read_params.hpp"
#include "grid_count.hpp"
#include "entropy_val.hpp"
#include "root_mean_square_distance.hpp"

int main(void){
	int n_molecules, lattice_size, n_iterations, seed;
	std::string ifile_name = "input/input.txt";
	read_params(ifile_name, n_molecules, lattice_size, n_iterations, seed);

	int dim = 2;
	std::vector<double> molecules(dim*n_molecules);
	for (int i = 0; i < n_molecules; i++){
		molecules[i] = 0.0;
	}
	// Aquí va el código de Juan Eliecer

	int grid_size = 8;
	std::vector<int> grid(grid_size*grid_size);
	grid_count(dim, n_molecules, lattice_size, grid_size, grid, molecules);

	double entropy;
	entropy = entropy_val(n_molecules, grid_size, grid);
	std::cout << entropy << std::endl;

	double root_mean_square;
	root_mean_square = root_mean_square_distance(dim, n_molecules, molecules);
	std::cout << root_mean_square << std::endl;
	return 0;
}