#pragma once

#include <cmath>

struct Vector2D {
    double x;
    double y;

    Vector2D(double x = 0.0, double y = 0.0) : x(x), y(y) {}

    Vector2D operator+(const Vector2D& o) const { return Vector2D(x + o.x, y + o.y); }
    Vector2D operator-(const Vector2D& o) const { return Vector2D(x - o.x, y - o.y); }
    Vector2D operator*(double s) const { return Vector2D(x * s, y * s); }
    Vector2D operator/(double s) const { return Vector2D(x / s, y / s); }

    Vector2D& operator+=(const Vector2D& o) {
        x += o.x;
        y += o.y;
        return *this;
    }

    double lengthSquared() const { return x * x + y * y; }
    double length() const { return std::sqrt(lengthSquared()); }

    Vector2D normalized() const {
        double len = length();
        return (len > 0.00001) ? (*this / len) : Vector2D(0, 0);
    }

    static double dot(const Vector2D& a, const Vector2D& b) {
        return a.x * b.x + a.y * b.y;
    }
};

struct Particle {
    int id;
    Vector2D position;
    Vector2D prevPosition;
    Vector2D velocity;
    Vector2D acceleration;
    double mass;
    double radius;
    double restitution; // Elasticity coefficient (0.0 to 1.0)

    Particle(int id, double x, double y, double vx, double vy, double mass = 1.0, double radius = 2.0)
        : id(id), position(x, y), prevPosition(x - vx * 0.016, y - vy * 0.016),
          velocity(vx, vy), acceleration(0, 0), mass(mass), radius(radius), restitution(0.92) {}

    void applyForce(const Vector2D& force) {
        if (mass > 0.0) {
            acceleration += force / mass;
        }
    }
};
