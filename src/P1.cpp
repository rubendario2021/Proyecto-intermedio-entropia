#include "read_params.hpp"
#include "grid_count.hpp"
#include "entropy_val.hpp"
#include "initialize_position.hpp"
#include "root_mean_square_distance.hpp"
#include "random_movement.hpp"
#include "save_molecules.hpp"

int main(void){
	// Key that show the code (change)
	std::string problem_id = "1";
	// Definition of the entries in the file "input.txt" as integers
	int n_molecules, lattice_size, n_iterations, seed;
	// Call the file "input.txt" and call a function to read the variables
	std::string ifile_name = "input/input.txt";
	read_params(ifile_name, n_molecules, lattice_size, n_iterations, seed);
	// Creation of the matrix of particle positions
	int dim = 2;
	std::vector<double> molecules(dim*n_molecules);
	// Definition of the initial positions of the molecules
	initialize_position(dim, n_molecules, lattice_size, molecules);
	// Definition of the container size for probability
	int grid_size = 8;
	std::vector<int> grid(grid_size*grid_size);
	// The random number generator engine is created before the function to avoid initializing it on each call
    std::mt19937 gen(seed);
    std::uniform_int_distribution<int> direction_distribution(0, 3);
	// Definition of some values to save
	double entropy;
	double root_mean_square;
	// Definition of a dynamic file name
	std::string ofile_name = "output/P" + problem_id + "/parameters_" + std::to_string(grid_size) + ".txt";
	std::ofstream output_params(ofile_name);
	// The code is iterated to perform the movement of the particle and the respective calculations
	n_iterations = 10000;
	for(int i = 0; i < n_iterations; i++) {
		// A random movement of the particles is generated
		random_movement(dim, n_molecules, lattice_size, seed, molecules, gen, direction_distribution);
		// Counting the number of nodes at each cell grid
		grid_count(dim, n_molecules, lattice_size, grid_size, grid, molecules);
		// Calculation of the system's entropy
		entropy = entropy_val(n_molecules, grid_size, grid);
		// Calculation of the root mean square distance
		root_mean_square = root_mean_square_distance(dim, n_molecules, molecules);
		// Saving parameters in its file
		output_params << i << "\t" << entropy << "\t" << root_mean_square << std::endl;
		// Condition to save molecules position
		if (i%10 == 0) {
			// Saving into a text file the coordinates of the molecules for plotting
			save_molecules(i, problem_id, dim, n_molecules, molecules);
		}
	}
	// Closing the parameters file
	output_params.close();
	return 0;
}