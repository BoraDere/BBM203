#include "Sector.h"
#include <cmath>
#include <iostream>

// Constructor implementation

Sector::Sector(int x, int y, int z) : x(x), y(y), z(z), left(nullptr), right(nullptr), parent(nullptr), color(RED) {
        // TODO: Calculate the distance to the Earth, and generate the sector code
        double distance_from_earth = (double)std::sqrt(x*x + y*y + z*z);
        this->distance_from_earth = distance_from_earth;
        sector_code += std::to_string((int)distance_from_earth);

        sector_code += (x == 0 ? 'S' : (x > 0 ? 'R' : 'L'));
        sector_code += (y == 0 ? 'S' : (y > 0 ? 'U' : 'D'));
        sector_code += (z == 0 ? 'S' : (z > 0 ? 'F' : 'B'));
}

Sector::~Sector() {
    // TODO: Free any dynamically allocated memory if necessary 
}

Sector& Sector::operator=(const Sector& other) {
    // TODO: Overload the assignment operator
    if (this != &other) {
        x = other.x;
        y = other.y;
        z = other.z;
        left = nullptr; 
        right = nullptr;
        parent = nullptr;
        color = other.color;
        distance_from_earth = other.distance_from_earth;
        sector_code = other.sector_code;
    }
    return *this;
}

bool Sector::operator==(const Sector& other) const {
    return (x == other.x && y == other.y && z == other.z);
}

bool Sector::operator!=(const Sector& other) const {
    return !(*this == other);
}