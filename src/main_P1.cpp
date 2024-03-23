#include <iostream>
#include "utilities/read_params.hpp"

int main(void){
	int nmolecules, latticesize, niterations, seed;
	std::cout << nmolecules << " " << latticesize << " " << niterations \
			  << " " << seed << "\n";
	std::string ifile_name = "input.txt";
	read_params(ifile_name, nmolecules, latticesize, niterations, seed);
	std::cout << nmolecules << " " << latticesize << " " << niterations \
			  << " " << seed << "\n";
	return 0;
}