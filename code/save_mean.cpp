#include "save_mean.hpp"

void save_mean(int &n_iterations, int &save_step, int &problem_id, std::vector<double> &mean) {
	std::string file_name = "output/P" + std::to_string(problem_id) + "/mean.txt";
	std::ofstream output_file(file_name);
	if (output_file.is_open()) {
        for (int i = 0; i < n_iterations/save_step; i++) {
            output_file << (i+1)*save_step << "\t" << std::fixed << std::setprecision(10) << mean[i] << std::endl;
        }
        output_file.close();
    } else {
		std::cerr << "Error: Output file " + file_name + " was not created.";
    }
}