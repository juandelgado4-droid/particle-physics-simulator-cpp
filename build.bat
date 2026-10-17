@echo off
echo Building 2D Particle Physics Simulator (C++)...
g++ -std=c++17 -Wall -Wextra -O2 -Iinclude src/PhysicsWorld.cpp src/main.cpp -o physics_sim.exe
if %ERRORLEVEL% EQU 0 (
    echo Build succeeded! Executing simulation...
    physics_sim.exe
) else (
    echo Build failed. Make sure G++ is installed.
)
