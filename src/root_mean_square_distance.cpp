#include "root_mean_square_distance.hpp"

double root_mean_square_distance(int &dim, int &n_molecules, std::vector<double> &molecules) {
	double root_mean_square, sum = 0.0;
	double coord_x, coord_y;
	int pos_x = 0, pos_y = 1;
	for (int i = 0; i < n_molecules; i++) {
		coord_x = molecules[i*dim + pos_x];
		coord_y = molecules[i*dim + pos_y];
		sum += (coord_x*coord_x + coord_y*coord_y);
	}
	root_mean_square = std::sqrt(sum/n_molecules);
	return root_mean_square;
}