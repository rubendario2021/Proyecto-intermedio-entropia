#include "save_molecules.hpp"

void save_molecules(int &iter, int &problem_id, int &dim, int &n_molecules, std::vector<double> &molecules) {
	std::string file_name = "output/P" + std::to_string(problem_id) + "/molecules_t_" + std::to_string(iter) + ".txt";
	std::ofstream output_file(file_name);
	int pos_x = 0, pos_y = 1;
	if (output_file.is_open()) {
        for (int i = 0; i < n_molecules; i++) {
            output_file << molecules[i*dim + pos_x] << "\t" << molecules[i*dim + pos_y] << std::endl;
        }
        output_file.close();
    } else {
		std::cerr << "Error: Output file " + file_name + " was not created.";
    }
}