#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch2/catch.hpp"
#include "project_headers.hpp"

TEST_CASE("System entropy is calculed", "[entropy_val]") {
	
	double eps = 1e-6;

	SECTION("All molecules in one grid") {
		int n_molecules = 20;
		int grid_size = 4;
		std::vector<int> grid(grid_size*grid_size, 0);
		grid[10] = 20;

		double entropy = entropy_val(n_molecules, grid_size, grid);

		REQUIRE(std::fabs(entropy - 0.0) <= eps);
	}

	SECTION("Same amount of molecules in each grid") {
		int n_molecules = 20;
		int grid_size = 2;
		std::vector<int> grid(grid_size*grid_size, 5);

		double val = (-std::log(0.25));
		double entropy = entropy_val(n_molecules, grid_size, grid);

		REQUIRE(std::fabs((entropy - val))/val <= eps);
	}
}

TEST_CASE("Number of molecules in each grid given its position", "[grid_count]") {

	/*
	Is important take into account that the function random_movement guarantees that all the molecules
	will be in the following range (-lattice_size/2.0, lattice_size/2.0)
	*/ 

	SECTION("All molecules in the origin") {
		int dim = 2;
		int lattice_size = 4;
		int n_molecules = 20;
		int grid_size = 4;

		std::vector<double> molecules(dim*n_molecules, 0.0);
		std::vector<int> grid(grid_size*grid_size, 0);

		grid_count(dim, n_molecules, lattice_size, grid_size, grid, molecules);
		
		/*
		Given grid_size, each square cell has a length of lattice_size/grid_size = 1
		That is, the cells will store the positions in the following ranges [-2, -1) [-1, 0) [0, 1) [1, 2)
		Therefore, in cell 2, 2 there will be 20 molecules 
		*/ 

		REQUIRE(grid[2*grid_size + 2] == 20);
	}

	SECTION("One molecule in each quadrant") {
		int dim = 2;
		int lattice_size = 4;
		int n_molecules = 4;
		int grid_size = 2;

		std::vector<double> molecules(dim*n_molecules, 0.0);
		
		// Molecule 1 - Quadrant I
		molecules[0*dim + 0] = {1.9999};
		molecules[0*dim + 1] = {0.0001};

		// Molecule 2 - Quadrant II
		molecules[1*dim + 0] = {-1.9999};
		molecules[1*dim + 1] = {0.0001};

		// Molecule 3 - Quadrant III
		molecules[2*dim + 0] = {-1.9999};
		molecules[2*dim + 1] = {-0.0001};

		// Molecule 4 - Quadrant IV
		molecules[3*dim + 0] = {1.9999};
		molecules[3*dim + 1] = {-0.0001};

		std::vector<int> grid(grid_size*grid_size, 0);
		grid_count(dim, n_molecules, lattice_size, grid_size, grid, molecules);
		
		/*
		Given grid_size, each square cell has a length of lattice_size/grid_size = 2
		That is, the cells will store the positions in the following ranges [-2, 0) [0, 2)
		Therefore, in each cell there will be 1 molecules 
		*/ 

		REQUIRE(grid[0*grid_size + 0] == 1);
		REQUIRE(grid[0*grid_size + 1] == 1);
		REQUIRE(grid[1*grid_size + 0] == 1);
		REQUIRE(grid[1*grid_size + 1] == 1);
	}
}