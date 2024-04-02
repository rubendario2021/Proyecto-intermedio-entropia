#include "project_headers.hpp"

int main(int argc, char *argv[]){
	// Key that indicate the problem to solve
	int problem_id = 3;
	int count_out = 0;

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

	// Definition of some values to save and optimize output files
	int save_step = 100000;
	int values_saved = n_iterations/save_step;
	std::vector<double> rmsd(values_saved, 0.0);
	std::vector<double> time(values_saved, 0.0);
		
	// The random number generator engine is created before the function to avoid initializing it on each call
	std::mt19937 gen(seed);
	std::uniform_int_distribution<int> direction_distribution(0, 3);
	
	// The code is iterated to perform the movement of molecules and their respective parameters
	for (int save_idx = 0; save_idx < values_saved; save_idx++) {

		// A random movement of the particles is generated
		for (int jj = 0; jj < save_step; jj++) {
			random_movement(dim, n_molecules, lattice_size, molecules, gen, direction_distribution, problem_id, count_out);
		}
			
		// Calculation of the system's entropy
		rmsd[save_idx] = rmsd_val(dim, n_molecules, molecules);
		time[save_idx] = static_cast<double>((save_idx+1) * save_step);
	}

	// Values to monomial fit
	double exponent = 0.0;
	double coefficient = 0.0;
	fit_monomial(time, rmsd, exponent, coefficient);

	// Saving rmsd data
	save_fit_rmsd(exponent, coefficient, problem_id, time, rmsd);
	
	return 0;
}