#include "project_headers.hpp"

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

	// Expansion to see convergence behaviour
	n_iterations *= 15;

	// Definition of some values to save and optimize output files
	int save_step = 2000;
	int values_saved = n_iterations/save_step;
	double entropy_i_1 = 0.0;
	double entropy_i = 0.0;

	// Statistics to show convergence of values (tested on entropy)
	/*
	This implementation is a quite rustic, but is useful to show a convergence plot, the idea of iterative
	algorithms is not to store the values inside a data structure but optimize processes
	*/ 
	double mean_val = 0.0;
	double alpha = 0.0; // Smooth factor
	double slope = 0.0;
	std::vector<double> mean(values_saved-1, 0.0);

	// The random number generator engine is created before the function to avoid initializing it on each call
    std::mt19937 gen(seed);
    std::uniform_int_distribution<int> direction_distribution(0, 3);
	
	// The code is iterated to perform the movement of molecules and their respective parameters
	for (int save_idx = 0; save_idx < values_saved; save_idx++) {
		
		// A random movement of the particles is generated
		for (int ii = 0; ii < save_step; ii++) {
			random_movement(dim, n_molecules, lattice_size, seed, molecules, gen, direction_distribution);
		}

		// Counting the number of nodes at each cell grid
		grid_count(dim, n_molecules, lattice_size, grid_size, grid, molecules);
			
		// Calculation of the system's entropy
		entropy_i_1 = entropy_i;
		entropy_i = entropy_val(n_molecules, grid_size, grid);
		
		// Calculation of statistics
		alpha = 1.0/(save_idx+1);
		slope = (entropy_i - entropy_i_1)/save_step;
		mean_val = (1-alpha)*mean_val + alpha*slope;
		
		mean[save_idx] = mean_val;
	}

	// Saving mean slope data
	save_mean_slope(n_iterations, save_step, problem_id, mean);
	return 0;
}