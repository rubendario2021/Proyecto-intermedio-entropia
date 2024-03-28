#include "read_params.hpp"
#include "grid_count.hpp"
#include "entropy_val.hpp"
#include "initialize_position.hpp"
#include "root_mean_square_distance.hpp"
#include "random_movement.hpp"
#include "P1.hpp"

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




	// Definition of the container size for probability
	int grid_size = 100;
	std::vector<int> grid(grid_size*grid_size);

	// The random number generator engine is created before the function to avoid initializing it on each call
    std::mt19937 gen(seed);
    std::uniform_int_distribution<int> direction_distribution(0, 3);

	// Definition of some values to print in the console
	double entropy;
	double root_mean_square;


	std::ofstream output_console_File("output/console.txt");

	// The code is iterated to perform the movement of the particle and the respective calculations
	for(int i=0; i<10000; i++){
		// A random movement of the particles is generated
		random_movement(dim, n_molecules, lattice_size, seed, molecules, gen, direction_distribution);
		// Counting the number of nodes at each cell grid
		grid_count(dim, n_molecules, lattice_size, grid_size, grid, molecules);
		// Calculation of the system's entropy
		entropy = entropy_val(n_molecules, grid_size, grid);
		// Calculation of the root mean square distance
		root_mean_square = root_mean_square_distance(dim, n_molecules, molecules);

		output_console_File << i << "\t" << entropy << "\t" << root_mean_square << std::endl;
	}

	output_console_File.close();




	// Printing to a text file the coordinates of the molecules in the last iteration, for plotting
	std::ofstream outputFile("output/data.txt");
	int pos_x = 0, pos_y = 1;

	if (outputFile.is_open()) {
        for (int i = 0; i < n_molecules; i++) {
            outputFile << molecules[i*dim + pos_x] << "\t" << molecules[i*dim + pos_y] << std::endl;
        }
        outputFile.close();
        system("gnuplot src/graficar.plt");
    } else {
        return 1;
    }


	return 0;
}