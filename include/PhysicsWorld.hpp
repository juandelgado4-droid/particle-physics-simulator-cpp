#pragma once

#include "Particle.hpp"
#include <vector>
#include <string>

class PhysicsWorld {
public:
    PhysicsWorld(double width, double height, Vector2D gravity = Vector2D(0, 9.81));

    void addParticle(const Particle& p);
    void step(double dt);

    double getTotalKineticEnergy() const;
    Vector2D getTotalLinearMomentum() const;
    size_t getParticleCount() const { return particles.size(); }

    void renderASCII(std::vector<std::string>& grid, int gridW, int gridH) const;

    const std::vector<Particle>& getParticles() const { return particles; }

private:
    double worldW;
    double worldH;
    Vector2D gravity;
    std::vector<Particle> particles;

    void applyForces();
    void integrateVerlet(double dt);
    void resolveCollisions();
    void enforceBoundaries();
};
