#include "read_params.hpp"
#include "grid_count.hpp"
#include "entropy_val.hpp"
#include "initialize_position.hpp"
#include "root_mean_square_distance.hpp"
#include "random_movement.hpp"

int main(void){
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

	// Definition of the container size
	int grid_size = 16;
	std::vector<int> grid(grid_size*grid_size);

	//GEN DEFINITION
    std::mt19937 gen(seed);
    std::uniform_int_distribution<int> direction_distribution(0, 3);

	for(int i=0; i<50000; i++){
		// random movement
		random_movement(dim, n_molecules, lattice_size, seed, molecules, gen, direction_distribution);
		//Counting the number of nodes at each cell grid
		grid_count(dim, n_molecules, lattice_size, grid_size, grid, molecules); 
	}


	// Calculation of the system's entropy
	double entropy;
	entropy = entropy_val(n_molecules, grid_size, grid);
	std::cout << entropy << std::endl;

	// Calculation of the root mean square distance
	double root_mean_square;
	root_mean_square = root_mean_square_distance(dim, n_molecules, molecules);
	std::cout << root_mean_square << std::endl;
	return 0;
}