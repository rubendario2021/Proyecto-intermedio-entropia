#pragma once
#include <fstream>
#include <string>
#include <array>

void read_params(std::string file_name, int &nmolecules, int &latticesize, int &niterations, int &seed);