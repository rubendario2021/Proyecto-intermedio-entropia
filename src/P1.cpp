#include "read_params.hpp"
#include "grid_count.hpp"
#include "entropy_val.hpp"
#include "initialize_position.hpp"
#include "root_mean_square_distance.hpp"
#include "random_movement.hpp"
#include "save_molecules.hpp"
#include "save_rmsd.hpp"
#include "save_entropy.hpp"

int main(void){
	// Key that show the code (change)
	int problem_id = 1;
	// Definition of the entries in the file "input.txt" as integers
	int n_molecules = 0;
	int lattice_size = 0;
	int n_iterations = 0;
	int seed = 0;
	// Call the file "input.txt" and call a function to read the variables
	std::string ifile_name = "input/input.txt";
	read_params(ifile_name, n_molecules, lattice_size, n_iterations, seed);
	// Creation of the matrix of particle positions
	int dim = 2;
	int idx = 0;
	std::vector<double> molecules(dim*n_molecules, 0.0);
	// Definition of the initial positions of the molecules
	initialize_position(dim, n_molecules, lattice_size, molecules);
	// Saving into a text file the coordinates of the molecules for plotting
	save_molecules(idx, problem_id, dim, n_molecules, molecules);
	// Definition of the container size for probability
	int grid_size = 8;
	std::vector<int> grid(grid_size*grid_size, 0);
	// The random number generator engine is created before the function to avoid initializing it on each call
    std::mt19937 gen(seed);
    std::uniform_int_distribution<int> direction_distribution(0, 3);
	// Definition of some values to save and optimize script
	int save_step = 2000;
	// Expansion to see stabilization of parameters
	// n_iterations *= 6;
	n_iterations = 100000;
	int save_idx = 0;
	std::vector<double> entropy(n_iterations/save_step, 0.0);
	// std::vector<double> rmsd(n_iterations/save_step, 0.0);
	// The code is iterated to perform the movement of the particle and the respective calculations
	for(idx = 1; idx <= n_iterations; idx++) {
		if (idx%10000 == 0) std::cout << idx << std::endl;
		// A random movement of the particles is generated
		random_movement(dim, n_molecules, lattice_size, seed, molecules, gen, direction_distribution);
		// Counting the number of nodes at each cell grid
		grid_count(dim, n_molecules, lattice_size, grid_size, grid, molecules);
		if (idx%save_step == 0) {
			save_idx = idx/save_step - 1;
			// Calculation of the system's entropy
			entropy[save_idx] = entropy_val(n_molecules, grid_size, grid);
			// Calculation of the root mean square distance
			// rmsd[save_idx] = root_mean_square_distance(dim, n_molecules, molecules);
		}
		// Condition to save molecules position
		if ((idx == 1e4) || (idx == 1e5) || (idx == 1e6)) {
			// Saving into a text file the coordinates of the molecules for plotting
			save_molecules(idx, problem_id, dim, n_molecules, molecules);
		}
	}
	// Saving parameters
	save_entropy(n_iterations, save_step, problem_id, grid_size, entropy);
	// save_rmsd(n_iterations, save_step, problem_id, rmsd);
	return 0;
}