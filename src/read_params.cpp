#include "../include/read_params.hpp"

void read_params(std::string file_name, int &nmolecules, int &latticesize, int &niterations, int &seed){
	std::array<int &, 4> input_params = {&nmolecules, &latticesize, &niterations, &seed};
	std::ifstream file;
	file.open(file_name);
	for (int i = 0; file >> input_params[i]; i++)
	file.close();
}