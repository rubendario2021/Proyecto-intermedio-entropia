#include "entropy_val.hpp"

double entropy_val(int &n_molecules, int &grid_size, std::vector<int> &grid) {
	double entropy;
	for (int i = 0; i < (grid_size*grid_size); i++) {
		int count = grid[i];
		if (count == 0) {
			continue;
		} else {
			double P_i = static_cast<double>(count)/n_molecules;
			entropy += (-P_i * std::log(P_i));
		}
	}
	return entropy;
}