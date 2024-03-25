#pragma once
#include <cmath>
#include <vector>

double entropy_val(int dim, int n_molecules, int lattice_size, int grid_size, std::vector<int> &grid_count, std::vector<double> &particles);
