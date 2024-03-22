#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <map>

struct Particula {
    int x, y;
};

bool colision(const Particula &a, const Particula &b) {
    return a.x == b.x && a.y == b.y;
}

Particula rebote(const Particula &p, int direccion) {
    // Este es un enfoque simplificado. En una situación real, querrías ajustar
    // esta función para manejar correctamente el rebote en varias direcciones.
    switch (direccion) {
        case 0: return {p.x, p.y - 1}; // Arriba
        case 1: return {p.x, p.y + 1}; // Abajo
        case 2: return {p.x - 1, p.y}; // Izquierda
        case 3: return {p.x + 1, p.y}; // Derecha
        default: return p;
    }
}

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    const int size = 150;
    std::vector<std::vector<int>> matriz(size, std::vector<int>(size, 0));
    
    int num_ciclos = 100;
    double matriz_transicion[4] = {0.25, 0.25, 0.25, 0.25};
    std::discrete_distribution<> distribucion(matriz_transicion, matriz_transicion + 4);

    // Crear un grupo de partículas
    std::vector<Particula> particulas = {{75, 75}}; // Comenzamos con una partícula central
    // Añadir partículas alrededor de la central
    for (int dx = -2; dx <= 2; ++dx) {
        for (int dy = -2; dy <= 2; ++dy) {
            if (dx == 0 && dy == 0) continue; // Omitir la partícula central
            particulas.push_back({75 + dx * 10, 75 + dy * 10});
        }
    }

    // Marcar la condición inicial en la matriz
    for (auto &p : particulas) {
        matriz[p.x][p.y] = 1;
    }

    // Guardar la condición inicial
    std::ofstream archivo_inicial("condicion_inicial.txt");
    for (const auto &fila : matriz) {
        for (int val : fila) {
            archivo_inicial << val << " ";
        }
        archivo_inicial << "\n";
    }
    archivo_inicial.close();

    // Limpiar la matriz para la simulación
    for (auto &fila : matriz) {
        std::fill(fila.begin(), fila.end(), 0);
    }

    // Simulación con rebote
    for (int t = 0; t < num_ciclos; ++t) {
        for (auto &particula : particulas) {
            int direccion = distribucion(gen);
            Particula nueva_pos = rebote(particula, direccion);

            // Comprobar colisiones para implementar el rebote
            bool hay_colision = false;
            for (auto &otra : particulas) {
                if (&particula != &otra && colision(nueva_pos, otra)) {
                    hay_colision = true;
                    break;
                }
            }

            if (!hay_colision) {
                particula = nueva_pos;
            } else {
                // En caso de colisión, podríamos implementar un rebote real aquí.
                // Por ahora, simplemente no movemos la partícula.
            }

            // Actualizar la matriz
            matriz[particula.x][particula.y] = t + 1; // Marcamos con el ciclo para ver el camino
        }
    }

    // Guardar la matriz final
    std::ofstream archivo("matriz_final.txt");
    for (const auto &fila : matriz) {
        for (int val : fila) {
            archivo << val << " ";
        }
        archivo << "\n";
    }
    archivo.close();

    return 0;
}
