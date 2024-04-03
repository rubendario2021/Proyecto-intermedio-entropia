#include "save_computing_time.hpp"

void save_computing_time(int &problem_id, int &number_sizes, std::vector<double> &computing_time, std::vector<double> &sizes) {
  // The text file is opened
	std::string file_name = "output/P" + std::to_string(problem_id) + "/Computing_time.txt";

  // The information about position x and y is saved in the text file
	std::ofstream output_file(file_name);
	if (output_file.is_open()) {
        for (int i = 0; i < number_sizes; i++) {
            output_file << std::fixed << std::setprecision(6) << sizes[i] << "\t" << computing_time[i] << std::endl;
        }
        output_file.close();
    } else {
		std::cerr << "Error: Output file " + file_name + " was not created." << std::endl;
    }
}