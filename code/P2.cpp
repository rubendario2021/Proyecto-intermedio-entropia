#include "project_headers.hpp"

int main(int argc, char *argv[]){
	// Key that indicate the problem to solve
	int problem_id = 2;

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

	// Definition of the container size for probability
	int grid_size = 8;
	std::vector<int> grid(grid_size*grid_size, 0);

	// Maximum value of entropy and convergence rate
	double max_entropy = -std::log(1.0/(grid_size*grid_size));
	double tol = 0.975;
	double perc = 0.0;

	// Definition of some values to save and optimize output files
	int save_step = 2000;
	double t_i = 1.0;
	double entropy_i = 0.0;

	// Different lattice_size
	int number_sizes = 5;
	double d_lattice_size = static_cast<double>(lattice_size);
	int size = 0;
	std::vector<double> sizes(number_sizes, 0);
	sizes = {d_lattice_size/4, d_lattice_size/2, d_lattice_size, d_lattice_size*3/2, d_lattice_size*2};

	// Storage to time
	std::vector<double> time(number_sizes, 0.0);

	for (int ii = 0; ii < number_sizes; ii++) {

		size = static_cast<int>(sizes[ii]);
		
		// The random number generator engine is created before the function to avoid initializing it on each call
		std::mt19937 gen(seed);
		std::uniform_int_distribution<int> direction_distribution(0, 3);

		// Definition of the initial positions of the molecules
		initialize_position(dim, n_molecules, size, molecules);
		
		// The code is iterated to perform the movement of molecules and their respective parameters
		while (perc < tol) {

			// A random movement of the particles is generated
			for (int jj = 0; jj < save_step; jj++) {
				random_movement(dim, n_molecules, size, molecules, gen, direction_distribution);
			}

			// Counting the number of nodes at each cell grid
			grid_count(dim, n_molecules, size, grid_size, grid, molecules);
				
			// Calculation of the system's entropy
			entropy_i = entropy_val(n_molecules, grid_size, grid);

			// Calculation of the percentage of entropy respect to its maximum
			perc = std::fabs(entropy_i/max_entropy);

			t_i++;
		}

		// Saving time required
		time[ii] = t_i*save_step;
		t_i = 1.0;

		// Restarting condition
		perc = 0.0;	
	}

	// Values to monomial fit
	double exponent = 0.0;
	double coefficient = 0.0;
	fit_monomial(sizes, time, exponent, coefficient);

	save_fit_ts(exponent, coefficient, problem_id, sizes, time);
	
	return 0;
}