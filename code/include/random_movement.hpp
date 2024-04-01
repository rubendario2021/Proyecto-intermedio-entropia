#pragma once
#include <vector>
#include <random>
#include <iostream>
#include <cmath>

void random_movement(int &dim, int &n_molecules, int &lattice_size, std::vector<double> &molecules, std::mt19937 &gen, std::uniform_int_distribution<int> &direction_distribution, int &problem_id, int &count_out);