#include "read_params.hpp"
#include "entropy_val.hpp"

int main(void){
	int n_molecules, lattice_size, n_iterations, seed;
	std::string ifile_name = "input/input.txt";
	read_params(ifile_name, &n_molecules, &lattice_size, &n_iterations, &seed);
	
	int dim = 2;
	std::vector<double> particles(dim * n_molecules);
	for (int i = 0; i < particles.size(); i++){
		particles[i] = 0.0;
	}
	particles[0] = {-1.5};
	particles[1] = {-9.5};

	int grid_size = 8;
	std::vector<int> grid_count(grid_size * grid_size);
	double entropy = entropy_val(dim, n_molecules, lattice_size, grid_size, grid_count, particles);
	for (int i = 0; i < grid_size; i++){
		for (int j = 0; j < grid_size; j++){
			std::cout << grid_count[j*grid_size + i] << " ";
		}
		std::cout << "\n";
	}
	
	return 0;
}