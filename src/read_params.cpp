#include "read_params.hpp"

void read_params(std::string &file_name, int &n_molecules, int &lattice_size, int &n_iterations, int &seed){
	std::ifstream file(file_name);
	// The text file is opened
	if (file.is_open()) {
		std::string line = ""; // Creation of a variable to store the lines of the text file
		int line_number = 0;

		while (std::getline(file, line)) {
			int value = std::stoi(line);
			// Switch statement is used to store the variables line by line
			switch (line_number) {
				case 0: n_molecules = value; break;
				case 1: lattice_size = value; break;
				case 2: n_iterations = value; break;
				case 3: seed = value; break;
				default: std::cerr << "Error: More lines in file than expected." << std::endl;
			}
			line_number++;
		}
		file.close();
	} else {
		std::cerr << "Error: File " + file_name + " was not found."<< std::endl; 
	}
}