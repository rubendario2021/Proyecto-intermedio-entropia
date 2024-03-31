// test_entropy_val.cpp

#define CATCH_CONFIG_MAIN  // Esto le dice a Catch2 que genere una función main
#include "/workspaces/Proyecto-intermedio-entropia/Catch2-2.13.5/Catch2-2.13.5/include/catch.hpp"

#include "/workspaces/Proyecto-intermedio-entropia/code/include/entropy_val.hpp"  // Ajusta la ruta según la estructura de tu proyecto

// Prueba para calcular la entropía de un grid vacío
TEST_CASE("Entropy of an empty grid is zero", "[entropy]") {
    int n_molecules = 0;
    int grid_size = 2;
    std::vector<int> grid(grid_size * grid_size, 0); // Un grid 2x2 vacío

    double result = entropy_val(n_molecules, grid_size, grid);
    REQUIRE(result == 0.0); // Eliminamos Approx ya que estamos comparando valores enteros
}

// Prueba para calcular la entropía cuando todas las moléculas están en una sola celda
TEST_CASE("Entropy of a grid with all molecules in one cell is zero", "[entropy]") {
    int n_molecules = 10;
    int grid_size = 2;
    std::vector<int> grid(grid_size * grid_size, 0);
    grid[0] = n_molecules; // Todas las moléculas en una sola celda

    double result = entropy_val(n_molecules, grid_size, grid);
    REQUIRE(result == 0.0); // Eliminamos Approx ya que estamos comparando valores enteros
}

// Prueba para calcular la entropía con una distribución uniforme de moléculas
TEST_CASE("Entropy of a uniformly distributed grid is calculated correctly", "[entropy]") {
    int n_molecules = 4;
    int grid_size = 2;
    std::vector<int> grid = {1, 1, 1, 1}; // Distribución uniforme en un grid 2x2

    double result = entropy_val(n_molecules, grid_size, grid);
    // Calcula el valor esperado de entropía para esta distribución
    double expected_entropy = -std::log(0.25) * 4;
    REQUIRE(result == expected_entropy); // Eliminamos Approx ya que estamos comparando valores enteros
}