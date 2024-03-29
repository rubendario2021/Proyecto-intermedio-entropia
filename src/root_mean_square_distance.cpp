#include "root_mean_square_distance.hpp"

double root_mean_square_distance(int &dim, int &n_molecules, std::vector<double> &molecules) {
	// Creation of auxiliar variables to calculate rsmd
	double sum = 0.0;
	// Creation of coordinates and index
	double coord_x = 0.0, coord_y = 0.0;
	int pos_x = 0, pos_y = 1;
    // To calculate the root mean square distance, the Pythagorean theorem is applied, so the radius is: r^2 = x^2 + y^2
	for (int i = 0; i < n_molecules; i++) {
		coord_x = molecules[i*dim + pos_x];
		coord_y = molecules[i*dim + pos_y];
		sum += (coord_x*coord_x + coord_y*coord_y);
	}
    // Applying formula
	double root_mean_square = std::sqrt(sum/n_molecules);
	return root_mean_square;
}