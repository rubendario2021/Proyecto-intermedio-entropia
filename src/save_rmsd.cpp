#include "save_rmsd.hpp"

void save_rmsd(int &n_iterations, int &save_step, int &problem_id, std::vector<double> &rmsd) {
	std::string file_name = "output/P" + std::to_string(problem_id) + "/rmsd.txt";
	std::ofstream output_file(file_name);
	if (output_file.is_open()) {
        for (int i = 0; i < n_iterations/save_step; i++) {
            output_file << (i+1)*save_step << "\t" << rmsd[i] << std::endl;
        }
        output_file.close();
    } else {
		std::cerr << "Error: Output file " + file_name + " was not created.";
    }
}