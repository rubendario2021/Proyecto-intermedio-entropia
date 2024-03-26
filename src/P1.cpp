#include "read_params.hpp"
#include "grid_count.hpp"
#include "entropy_val.hpp"

int main(void){
	int n_molecules, lattice_size, n_iterations, seed;
	std::string ifile_name = "input/input.txt";
	read_params(ifile_name, &n_molecules, &lattice_size, &n_iterations, &seed);
<<<<<<< HEAD
=======
	
	int dim = 2;
	std::vector<double> particles(dim*n_molecules);
	for (int i = 0; i < n_molecules; i++){
		particles[i] = 0.0;
	}
	// Aquí va el código de Juan Eliecer

	int grid_size = 8;
	std::vector<int> grid(grid_size*grid_size);
	grid_count(dim, n_molecules, lattice_size, grid_size, grid, particles);

	double entropy;
	entropy = entropy_val(n_molecules, grid_size, grid);
	std::cout << entropy << std::endl;
>>>>>>> entropy
	return 0;
}