#include "../include/simulation.h"

Simulation::Simulation(double coef_friction, double gravity)
    : mu(coef_friction), g(gravity) {}

double Simulation::energy_of(Particle p, double t) {
  return 0.5 * p.m * (p.v0 - mu * g * t) * (p.v0 - mu * g * t);
}

double Simulation::velocity_of(Particle p, double t) {
  return p.v0 - mu * g * t;
}

double Simulation::stop_distance_of(Particle p) {
  return 0.5 * ((p.v0 * p.v0) / (2 * mu * g));
}

bool Simulation::collision(Particle p1, Particle p2) {
  return (p1.v0 - p2.v0) != 0;
};
