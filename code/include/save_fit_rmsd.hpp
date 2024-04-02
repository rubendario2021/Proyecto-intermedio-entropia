#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>

void save_fit_rmsd(double &exponent, double &coefficient, int &problem_id, std::vector<double> &time, std::vector<double> &rmsd);