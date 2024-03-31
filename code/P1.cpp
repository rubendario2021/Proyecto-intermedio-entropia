#include "read_params.hpp"
#include "grid_count.hpp"
#include "entropy_val.hpp"
#include "initialize_position.hpp"
#include "rmsd_val.hpp"
#include "random_movement.hpp"
#include "save_molecules.hpp"
#include "save_rmsd.hpp"
#include "save_entropy.hpp"
#include "save_mean.hpp"

int main(int argc, char *argv[]){
	// Key that indicate the problem to solve
	int problem_id = 1;

	// Definition of the entries in the file "input.txt" as integers
	int n_molecules = 0;
	int lattice_size = 0;
	int n_iterations = 0;
	int seed = 0;
	// Call the file "input.txt" and a function to read the variables and assign them
	// Change this, make it console dependent
	std::string ifile_name = std::string(argv[1]);
	read_params(ifile_name, n_molecules, lattice_size, n_iterations, seed);

	// Creation of the matrix of particle positions
	int dim = 2;
	std::vector<double> molecules(dim*n_molecules, 0.0);
	// Definition of the initial positions of the molecules
	initialize_position(dim, n_molecules, lattice_size, molecules);

	// Saving into a text file the initial coordinates of the molecules for plotting
	int idx = 0;
	save_molecules(idx, problem_id, dim, n_molecules, molecules);

	// Definition of the container size for probability
	int grid_size = 8;
	std::vector<int> grid(grid_size*grid_size, 0);
	
	// Definition of some values to save and optimize output files
	int save_step = 2000;
	std::vector<double> entropy(n_iterations/save_step, 0.0);
	// Expansion to see stabilization of parameters
	if (n_iterations == 1e6) n_iterations *= 10;
	int save_idx = 0;
	double mean = 0.0;
	std::vector<double> vec_mean(n_iterations/save_step, 0.0);
	double tmp_entropy = 0.0;
	double rmse = 0.0;

	// The random number generator engine is created before the function to avoid initializing it on each call
    std::mt19937 gen(seed);
    std::uniform_int_distribution<int> direction_distribution(0, 3);
	
	// The code is iterated to perform the movement of molecules and their respective parameters
	for(idx = 1; idx <= n_iterations; idx++) {
		// A random movement of the particles is generated
		random_movement(dim, n_molecules, lattice_size, seed, molecules, gen, direction_distribution);

		// Condition to save some data 
		if (idx%save_step == 0) {
			// Correction to the index value
			save_idx = idx/save_step - 1;
			// Counting the number of nodes at each cell grid
			grid_count(dim, n_molecules, lattice_size, grid_size, grid, molecules);
			// Calculation of the system's entropy
			tmp_entropy = entropy_val(n_molecules, grid_size, grid);
			entropy[save_idx] = tmp_entropy;
			mean += (tmp_entropy - mean)/(save_idx+1);
			rmse = std::sqrt(save_idx/(save_idx+1)*rmse*rmse + (tmp_entropy-mean)*(tmp_entropy-mean)/(save_idx+1));
			if (save_idx != 0) vec_mean[save_idx] = rmse;
			// Condition to save some molecules position
			if ((idx == 1e4) || (idx == 1e5) || (idx == 1e6)) {
				// Saving into a text file the coordinates of the molecules for plotting
				save_molecules(idx, problem_id, dim, n_molecules, molecules);
			}
		}
	}

	// Saving entropy data
	save_entropy(n_iterations, save_step, problem_id, entropy);
	save_mean(n_iterations, save_step, problem_id, vec_mean);
	return 0;
}