#include <iostream>
#include <fstream>
#include <vector>
#include <random>

class CreamInCoffee {
public:
    struct Particle { // Declarar la estructura Particle como pública
        int x, y; // Posición
    };

    CreamInCoffee(int num_particles, int grid_min, int grid_max, int seed)
        : num_particles(num_particles), grid_min(grid_min), grid_max(grid_max), seed(seed), gen(seed) {
        dis = std::uniform_int_distribution<int>(0, 3); // Para determinar la dirección de la caminata aleatoria
    }

    void initializeParticles();
    void runSimulation();
    void writeParticleData(const std::string& filename, const std::vector<Particle>& particles);

private:

    int num_particles; // Número de partículas
    int grid_min; // Mínimo valor del rango de la cuadrícula
    int grid_max; // Máximo valor del rango de la cuadrícula
    int seed; // Semilla para la generación de números aleatorios
    std::vector<Particle> particles; // Vector para almacenar las partículas
    std::mt19937 gen; // Motor para la generación de números aleatorios
    std::uniform_int_distribution<int> dis; // Distribución para movimientos de partículas

    void moveParticles();
};

void CreamInCoffee::initializeParticles() {
    particles.clear(); // Limpiar cualquier partícula existente

    // Definir los límites de la cuadrícula central
    int central_grid_min = -20; // -20 para centrar la cuadrícula de 20x20 en el origen
    int central_grid_max = 20;  // 20 para centrar la cuadrícula de 20x20 en el origen

    std::uniform_int_distribution<int> x_dist(central_grid_min, central_grid_max);
    std::uniform_int_distribution<int> y_dist(central_grid_min, central_grid_max);

    for (int i = 0; i < num_particles; ++i) {
        Particle particle;
        particle.x = x_dist(gen); // Generar x dentro de la cuadrícula central
        particle.y = y_dist(gen); // Generar y dentro de la cuadrícula central
        particles.push_back(particle);
    }
}

void CreamInCoffee::moveParticles() {
    for (auto& particle : particles) {
        int direction = dis(gen); // Generar dirección aleatoria (0: arriba, 1: abajo, 2: izquierda, 3: derecha)

        // Mover la partícula en la dirección determinada
        switch (direction) {
            case 0: // Arriba
                if (particle.y < grid_max) particle.y++;
                break;
            case 1: // Abajo
                if (particle.y > grid_min) particle.y--;
                break;
            case 2: // Izquierda
                if (particle.x > grid_min) particle.x--;
                break;
            case 3: // Derecha
                if (particle.x < grid_max) particle.x++;
                break;
        }
    }
}

void CreamInCoffee::writeParticleData(const std::string& filename, const std::vector<Particle>& particles) {
    std::ofstream outfile(filename);
    if (outfile.is_open()) {
        for (const auto& particle : particles) {
            outfile << particle.x << " " << particle.y << std::endl;
        }
        outfile.close();
    } else {
        std::cerr << "Error: Unable to open file: " << filename << std::endl;
    }
}

void CreamInCoffee::runSimulation() {
    initializeParticles(); // Inicializa las partículas en la cuadrícula central

    // Escribe los datos de las partículas para t = 0
    writeParticleData("cream_in_coffee_particles_t0.txt", particles);

    // Ejecutar la simulación durante 10^4 iteraciones
    for (int i = 0; i < 10000; ++i) {
        moveParticles();
    }

    // Escribe los datos de las partículas para t = 10^4
    writeParticleData("cream_in_coffee_particles_t10000.txt", particles);
}

int main() {
    int num_particles = 400;
    int grid_min = -200;
    int grid_max = 200;
    int seed = 0;

    CreamInCoffee simulation(num_particles, grid_min, grid_max, seed);
    simulation.runSimulation(); // Ejecutar la simulación

    return 0;
}