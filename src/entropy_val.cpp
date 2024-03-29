#include "entropy_val.hpp"

double entropy_val(int &n_molecules, int &grid_size, std::vector<int> &grid) {
	double entropy, P_i;
	int count;
	for (int i = 0; i < (grid_size*grid_size); i++) {
		count = grid[i];
		if (count == 0) {
			// If there are no particles in the grid cell, that cell is skipped from the analysis
			continue;
		} else {
			// The entropy is calculated as: sum[-P_i * ln(P_i)] where P_i is the probability associated with the cell
			P_i = static_cast<double>(count)/n_molecules;
			entropy += (-P_i * std::log(P_i));
		}
	}
	return entropy;
}