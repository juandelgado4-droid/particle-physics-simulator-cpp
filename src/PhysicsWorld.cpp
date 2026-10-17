#include "../include/PhysicsWorld.hpp"
#include <algorithm>
#include <iostream>

PhysicsWorld::PhysicsWorld(double width, double height, Vector2D gravity)
    : worldW(width), worldH(height), gravity(gravity) {}

void PhysicsWorld::addParticle(const Particle& p) {
    particles.push_back(p);
}

void PhysicsWorld::applyForces() {
    for (auto& p : particles) {
        // Reset acceleration to gravity
        p.acceleration = gravity;
    }
}

void PhysicsWorld::integrateVerlet(double dt) {
    for (auto& p : particles) {
        // Velocity Verlet integration: x(t+dt) = x(t) + v(t)*dt + 0.5*a(t)*dt^2
        Vector2D tempPos = p.position;
        Vector2D displacement = (p.position - p.prevPosition) + p.acceleration * (dt * dt);

        // Air damping / friction
        displacement = displacement * 0.999;

        p.prevPosition = tempPos;
        p.position += displacement;

        // Update instantaneous velocity
        p.velocity = (p.position - p.prevPosition) / dt;
    }
}

void PhysicsWorld::enforceBoundaries() {
    for (auto& p : particles) {
        // Left boundary
        if (p.position.x - p.radius < 0.0) {
            p.position.x = p.radius;
            p.prevPosition.x = p.position.x + p.velocity.x * p.restitution * 0.016;
        }
        // Right boundary
        if (p.position.x + p.radius > worldW) {
            p.position.x = worldW - p.radius;
            p.prevPosition.x = p.position.x + p.velocity.x * p.restitution * 0.016;
        }
        // Top boundary
        if (p.position.y - p.radius < 0.0) {
            p.position.y = p.radius;
            p.prevPosition.y = p.position.y + p.velocity.y * p.restitution * 0.016;
        }
        // Bottom boundary (floor)
        if (p.position.y + p.radius > worldH) {
            p.position.y = worldH - p.radius;
            p.prevPosition.y = p.position.y + p.velocity.y * p.restitution * 0.016;
        }
    }
}

void PhysicsWorld::resolveCollisions() {
    const size_t n = particles.size();
    for (size_t i = 0; i < n; i++) {
        for (size_t j = i + 1; j < n; j++) {
            Particle& p1 = particles[i];
            Particle& p2 = particles[j];

            Vector2D delta = p1.position - p2.position;
            double distSq = delta.lengthSquared();
            double minDist = p1.radius + p2.radius;

            if (distSq < minDist * minDist && distSq > 0.000001) {
                double dist = std::sqrt(distSq);
                Vector2D normal = delta / dist;

                // Overlap resolution (positional correction)
                double overlap = minDist - dist;
                double totalMass = p1.mass + p2.mass;

                p1.position += normal * (overlap * (p2.mass / totalMass));
                p2.position -= normal * (overlap * (p1.mass / totalMass));

                // Relative velocity
                Vector2D relVel = p1.velocity - p2.velocity;
                double velAlongNormal = Vector2D::dot(relVel, normal);

                if (velAlongNormal < 0.0) {
                    // Impulse scalar
                    double e = std::min(p1.restitution, p2.restitution);
                    double jImpulse = -(1.0 + e) * velAlongNormal / (1.0 / p1.mass + 1.0 / p2.mass);

                    Vector2D impulse = normal * jImpulse;
                    p1.velocity += impulse / p1.mass;
                    p2.velocity -= impulse / p2.mass;

                    // Update Verlet previous positions to maintain impulse velocity
                    p1.prevPosition = p1.position - p1.velocity * 0.016;
                    p2.prevPosition = p2.position - p2.velocity * 0.016;
                }
            }
        }
    }
}

void PhysicsWorld::step(double dt) {
    applyForces();
    integrateVerlet(dt);
    resolveCollisions();
    enforceBoundaries();
}

double PhysicsWorld::getTotalKineticEnergy() const {
    double totalKE = 0.0;
    for (const auto& p : particles) {
        totalKE += 0.5 * p.mass * p.velocity.lengthSquared();
    }
    return totalKE;
}

Vector2D PhysicsWorld::getTotalLinearMomentum() const {
    Vector2D totalP(0, 0);
    for (const auto& p : particles) {
        totalP += p.velocity * p.mass;
    }
    return totalP;
}

void PhysicsWorld::renderASCII(std::vector<std::string>& grid, int gridW, int gridH) const {
    grid.assign(gridH, std::string(gridW, ' '));

    // Outer border
    for (int x = 0; x < gridW; x++) {
        grid[0][x] = '-';
        grid[gridH - 1][x] = '-';
    }
    for (int y = 0; y < gridH; y++) {
        grid[y][0] = '|';
        grid[y][gridW - 1] = '|';
    }

    // Plot particles
    for (const auto& p : particles) {
        int gx = static_cast<int>((p.position.x / worldW) * (gridW - 2)) + 1;
        int gy = static_cast<int>((p.position.y / worldH) * (gridH - 2)) + 1;

        if (gx > 0 && gx < gridW - 1 && gy > 0 && gy < gridH - 1) {
            grid[gy][gx] = (p.mass > 2.0) ? 'O' : 'o';
        }
    }
}
