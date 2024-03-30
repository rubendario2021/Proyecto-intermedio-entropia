#pragma once
#include <vector>
#include <random>
#include <iostream>

void random_movement(int &dim, int &n_molecules, int &lattice_size, int &seed, std::vector<double> &molecules, std::mt19937 &gen, std::uniform_int_distribution<int> &direction_distribution);