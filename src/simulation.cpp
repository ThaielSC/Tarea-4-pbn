#include "../include/simulation.h"
#include <algorithm>
#include <cmath>

Simulation::Simulation(double coef_friction, double gravity)
    : mu(coef_friction), g(gravity) {}

double Simulation::stop_distance_of(Particle p) {
  return pow(p.get_velocity(), 2) / (2 * mu * g);
}

double Simulation::collision_time(Particle a, Particle b) {

  if (a.get_position() > b.get_position()) {
    std::swap(a, b);
  }

  if (a.get_velocity() - b.get_velocity() <= 0) {
    return -1.0;
  }

  return (b.get_position() - a.get_position()) /
         (a.get_velocity() - b.get_velocity());
}

double Simulation::particles_distance(Particle a, Particle b) {
  return fabs(a.get_position() - b.get_position());
}

bool Simulation::collision(Particle a, Particle b) {
  double tc = collision_time(a, b);

  if (tc < 0) {
    return false;
  }

  double tf_a = fabs(a.get_velocity()) / (mu * g);
  double tf_b = fabs(b.get_velocity()) / (mu * g);

  return tc <= std::min(tf_a, tf_b);
};
