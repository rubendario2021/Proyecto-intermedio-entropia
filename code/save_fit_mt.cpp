#include "save_fit_mt.hpp"

void save_fit_mt(double &exponent_coefficient, double &coefficient, int &problem_id, std::vector<double> &time, std::vector<double> &molecules_inside) {
  // The text file is opened
	std::string file_name = "output/P" + std::to_string(problem_id) + "/fit_mt_expon_" + std::to_string(exponent_coefficient * 1.0e6) + "_coeff_" + std::to_string(coefficient) + ".txt";

  // The information about the number of molecules vs time is saved in the text file
	std::ofstream output_file(file_name);
	if (output_file.is_open()) {
		int n_elements = static_cast<int>(time.size());
        for (int i = 0; i < n_elements; i++) {
            output_file << time[i] << "\t" << molecules_inside[i] << std::endl;
        }
        output_file.close();
    } else {
		std::cerr << "Error: Output file " + file_name + " was not created." << std::endl;
    }
}