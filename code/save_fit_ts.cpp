#include "save_fit_ts.hpp"

void save_fit_ts(double &exponent, double &coefficient, int &problem_id, std::vector<double> &sizes, std::vector<double> &time) {
  // The text file is opened
	std::string file_name = "output/P" + std::to_string(problem_id) + "/fit_ts_expon_" + std::to_string(exponent) + "_coeff_" + std::to_string(coefficient) + ".txt";

  // The information about root mean square distance vs time is saved in the text file
	std::ofstream output_file(file_name);
	if (output_file.is_open()) {
		int n_elements = static_cast<int>(sizes.size());
        for (int i = 0; i < n_elements; i++) {
            output_file << std::fixed << std::setprecision(6) << sizes[i] << "\t" << time[i] << std::endl;
        }
        output_file.close();
    } else {
		std::cerr << "Error: Output file " + file_name + " was not created.";
    }
}