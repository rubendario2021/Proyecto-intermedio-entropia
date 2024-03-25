#include "read_params.hpp"

int main(void){
	int n_molecules, lattice_size, n_iterations, seed;
	std::string ifile_name = "input/input.txt";
	read_params(ifile_name, &n_molecules, &lattice_size, &n_iterations, &seed);
	return 0;
}