#include "save_rmsd.hpp"

void save_rmsd(int &problem_id, std::vector<double> &time, std::vector<double> &rmsd) {
  // The text file is opened
	std::string file_name = "output/P" + std::to_string(problem_id) + "/rmsd.txt";

  // The information about root mean square distance vs time is saved in the text file
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