# ⚛️ 2D Particle Physics & Collision Engine (C++)

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)
[![C++ Standard](https://img.shields.io/badge/C%2B%2B-17-00599C?logo=c%2B%2B)](https://isocpp.org/)
[![Physics](https://img.shields.io/badge/Simulation-Verlet%20Integration-orange)]()

A high-performance 2D Newtonian particle physics simulator engineered in **C++17**. Implements Velocity Verlet numerical integration, elastic collision dynamics with coefficient of restitution, positional overlap resolution, and kinetic energy tracking.

---

## 🔬 Mathematical & Physical Principles

### 1. Velocity Verlet Numerical Integration
Provides superior numerical stability and energy conservation over simple Euler integration for oscillatory and dynamical particle systems:
$$\vec{x}(t + \Delta t) = 2\vec{x}(t) - \vec{x}(t - \Delta t) + \vec{a}(t) \Delta t^2$$

### 2. Elastic Collision Impulse Model
When two particles $i$ and $j$ with radii $r_i, r_j$ and velocities $\vec{v}_i, \vec{v}_j$ collide, the impulse scalar $J$ along normal $\hat{n}$ is:
$$J = \frac{-(1 + e)(\vec{v}_{\text{rel}} \cdot \hat{n})}{\frac{1}{m_i} + \frac{1}{m_j}}$$
where $e$ is the coefficient of restitution and $\vec{v}_{\text{rel}} = \vec{v}_i - \vec{v}_j$.

### 3. Positional Overlap Correction
Prevents sinking or particle tunneling by projecting overlapping spheres along the contact normal weighted inversely by mass ratio:
$$\Delta \vec{x}_i = \hat{n} \cdot \left(\text{overlap} \times \frac{m_j}{m_i + m_j}\right)$$

---

## 🚀 Building & Running

### Using Make (Linux / macOS / MinGW):
```bash
make
./physics_sim
```

### Using Windows CMD / PowerShell:
```bat
build.bat
```

---

## 📊 Sample Output

```
>>> [Step 50 | Time: 0.8s | Kinetic Energy: 432.18 J] <<<
|                                                          |
|        o                                                 |
|                O        o                o               |
|                                                          |
|                         o           O                    |
|             o         o                                  |
|   o                                                      |
|----------------------------------------------------------|
```

---

## 📄 License

This project is licensed under the [MIT License](LICENSE).
