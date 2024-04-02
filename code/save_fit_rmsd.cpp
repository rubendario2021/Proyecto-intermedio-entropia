#include "save_fit_rmsd.hpp"

void save_fit_rmsd(double &exponent, double &coefficient, int &problem_id, std::vector<double> &time, std::vector<double> &rmsd) {
  // The text file is opened
	std::string file_name = "output/P" + std::to_string(problem_id) + "/fit_rmsd_expon_" + std::to_string(exponent) + "_coeff_" + std::to_string(coefficient) + ".txt";

  // The information about root mean square distance fit function vs time is saved in the text file
	std::ofstream output_file(file_name);
	if (output_file.is_open()) {
		int n_elements = static_cast<int>(time.size());
        for (int i = 0; i < n_elements; i++) {
            output_file << time[i] << "\t" << rmsd[i] << std::endl;
        }
        output_file.close();
    } else {
		std::cerr << "Error: Output file " + file_name + " was not created." << std::endl;
    }
}