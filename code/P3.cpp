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
	std::string ifile_name = std::string(argv[1]); // Change this, make it console dependent
	read_params(ifile_name, n_molecules, lattice_size, n_iterations, seed);

	// Creation of the matrix of particle positions
	int dim = 2;
	std::vector<double> molecules(dim*n_molecules, 0.0);

	// Definition of the initial positions of the molecules
	initialize_position(dim, n_molecules, lattice_size, molecules);

	// Percentage of time at which entropy stabilizes
	int stabilization_time = static_cast<int>(7703.403*std::pow(lattice_size, 2.006)*0.7);
	
	// Skipped values to avoid initial tail
	int skipped = 100;

	// Definition of some values to save and optimize output files
	int save_step = 2000;
	int values_saved_1 = stabilization_time/save_step;
	int values_saved_2 = (n_iterations - stabilization_time)/save_step;
	int values_saved = values_saved_1 + values_saved_2;

	std::vector<double> rmsd_1(values_saved_1 - skipped, 0.0);
	std::vector<double> time_1(values_saved_1 - skipped, 0.0);
	std::vector<double> rmsd_2(values_saved_2, 0.0);
	std::vector<double> time_2(values_saved_2, 0.0);
		
	// The random number generator engine is created before the function to avoid initializing it on each call
	std::mt19937 gen(seed);
	std::uniform_int_distribution<int> direction_distribution(0, 3);
	
	// The code is iterated to perform the movement of molecules and their respective parameters
	for (int save_idx = 0; save_idx < values_saved; save_idx++) {

		// A random movement of the particles is generated
		for (int jj = 0; jj < save_step; jj++) {
			random_movement(dim, n_molecules, lattice_size, molecules, gen, direction_distribution, problem_id, count_out);
		}
			
		// Calculation of the rmsd of the molecules
		if (save_idx >= skipped) {
			if (save_idx < values_saved_1) {
				rmsd_1[save_idx - skipped] = rmsd_val(dim, n_molecules, molecules);
				time_1[save_idx - skipped] = static_cast<double>((save_idx+1) * save_step);
			} else { //Information continues to be stored for plotting the function, but not for calculating the function's fit
				rmsd_2[save_idx - values_saved_1] = rmsd_val(dim, n_molecules, molecules);
				time_2[save_idx - values_saved_1] = static_cast<double>((save_idx+1) * save_step);
			}
		} 
	}

	// Values to monomial fit
	double exponent = 0.0;
	double coefficient = 0.0;
	fit_monomial(time_1, rmsd_1, exponent, coefficient);

	// Saving rmsd data
	save_fit_rmsd(exponent, coefficient, problem_id, time_1, rmsd_1);
	save_rmsd(problem_id, time_2, rmsd_2);
	
	return 0;
}