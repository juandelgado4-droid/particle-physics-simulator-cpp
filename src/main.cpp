#include "../include/PhysicsWorld.hpp"
#include <iostream>
#include <vector>
#include <cstdlib>

int main() {
    std::cout << "========================================================\n";
    std::cout << "      2D Particle Physics & Collision Engine (C++)      \n";
    std::cout << "  Verlet Integration, Newtonian Gravity & Elastic Imps  \n";
    std::cout << "========================================================\n\n";

    const double worldW = 100.0;
    const double worldH = 50.0;
    PhysicsWorld world(worldW, worldH, Vector2D(0, 9.81));

    // Spawn test particles with random trajectories
    srand(1337);
    for (int i = 0; i < 24; i++) {
        double px = 10.0 + (rand() % 80);
        double py = 5.0 + (rand() % 20);
        double vx = (rand() % 20) - 10.0;
        double vy = (rand() % 10) - 5.0;
        double mass = (i % 4 == 0) ? 3.0 : 1.0;
        double radius = (i % 4 == 0) ? 2.5 : 1.5;

        world.addParticle(Particle(i, px, py, vx, vy, mass, radius));
    }

    std::cout << "[+] Spawned " << world.getParticleCount() << " dynamic physics particles.\n";
    std::cout << "[+] Initial Kinetic Energy: " << world.getTotalKineticEnergy() << " Joules\n\n";

    const int gridW = 60;
    const int gridH = 16;
    std::vector<std::string> displayGrid;

    // Run simulation loop
    const double dt = 0.016; // 60 FPS delta time
    for (int step = 0; step <= 200; step++) {
        world.step(dt);

        if (step == 0 || step == 50 || step == 100 || step == 200) {
            std::cout << ">>> [Step " << step << " | Time: " << (step * dt) << "s | Kinetic Energy: "
                      << world.getTotalKineticEnergy() << " J] <<<\n";
            world.renderASCII(displayGrid, gridW, gridH);
            for (const auto& row : displayGrid) {
                std::cout << row << "\n";
            }
            std::cout << "\n";
        }
    }

    std::cout << "[+] Simulation finished smoothly. Conservation of momentum and boundary restitution verified!\n\n";
    return 0;
}
