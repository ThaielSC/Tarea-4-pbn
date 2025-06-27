#include "../include/particle.hpp"

Particle::Particle(double mass, double init_pos, double init_vel)
    : _mass(mass), _position(init_pos), _velocity(init_vel) {}

double Particle::get_mass() { return _mass; }
double Particle::get_position() { return _position; }
double Particle::get_velocity() { return _velocity; }
