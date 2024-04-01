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

	// Definition of some values to save and optimize output files
	n_iterations *= 15;
	int save_step = 2000;
	int values_saved = n_iterations/save_step;
	double entropy_i_1 = 0.0;
	double entropy_i = 0.0;
	std::vector<double> entropy(values_saved, 0.0);
	std::vector<double> time(values_saved, 0.0);

	// Statistics to show convergence of values
	double mean_val = 1.0;
	double alpha = 0.0; // Smooth factor
	double slope = 0.0;
	double tol = 1e-6;

	// Unknown parameter for monomial y = a*x^(b)
	double exponent = 0.0;
	double coefficient = 0.0;

	// Different lattice_size
	std::vector<int> container_sizes(4, 0.0);
	container_sizes = {lattice_size/8, lattice_size/4, lattice_size/2, lattice_size};

	for (int size : container_sizes) {
		
		// The random number generator engine is created before the function to avoid initializing it on each call
		std::mt19937 gen(seed);
		std::uniform_int_distribution<int> direction_distribution(0, 3);

		// Definition of the initial positions of the molecules
		initialize_position(dim, n_molecules, size, molecules);
		
		int save_idx = 0;
		// The code is iterated to perform the movement of molecules and their respective parameters
		for (; save_idx < values_saved; save_idx++) {
		
			// A random movement of the particles is generated
			for (int ii = 0; ii < save_step; ii++) {
				random_movement(dim, n_molecules, size, molecules, gen, direction_distribution);
			}

			// Counting the number of nodes at each cell grid
			grid_count(dim, n_molecules, size, grid_size, grid, molecules);
				
			// Calculation of the system's entropy
			entropy_i_1 = entropy_i;
			entropy_i = entropy_val(n_molecules, grid_size, grid);
			entropy[save_idx] = entropy_i;

			// Storing time vector
			time[save_idx] = (save_idx+1) * save_step;

			// Calculation otime[save_idx]f statistics
			alpha = 1.0/(save_idx+1);
			slope = (entropy_i - entropy_i_1)/save_step;
			mean_val = (1-alpha)*mean_val + alpha*slope;

			if (mean_val <= tol) break;
		}

		std::cout << "size: " << size << " time: " << time[save_idx] << std::endl;
		// Saving entropy data
		save_entropy(n_iterations, save_step, problem_id, entropy);

		// Fitting monomial to experimental data
		fit_monomial(time, entropy, exponent, coefficient);
		std::cout << "Monomial fit: " << exponent << " " << coefficient << std::endl;

		// Restarting values and vectors
		mean_val = 1.0;
		entropy_i = 0.0;
		entropy_i_1 = 0.0;

		entropy.clear();
		entropy.resize(values_saved, 0.0);

		time.clear();
		time.resize(values_saved, 0.0);
	}
	
	return 0;
}