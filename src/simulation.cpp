#include "../include/simulation.h"
#include <algorithm>
#include <cmath>
#include <utility>

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

double Simulation::collision_position(Particle a, Particle b) {
  double timec = collision_time(a, b);
  return a.get_position() + (a.get_velocity() * timec) -
         (mu * g * pow(timec, 2)) / 2;
}

std::pair<double, double> Simulation::velocity_after_collision(Particle a,
                                                               Particle b) {
  return {((a.get_mass() - b.get_mass()) / (a.get_mass() + b.get_mass())) *
                  a.get_velocity() +
              ((2 * b.get_mass()) / (a.get_mass() + b.get_mass())) *
                  b.get_velocity(),
          ((b.get_mass() - a.get_mass()) / (a.get_mass() + b.get_mass())) *
                  b.get_velocity() +
              ((2 * a.get_mass()) / (a.get_mass() + b.get_mass())) *
                  a.get_velocity()

  };
}

std::pair<double, double> Simulation::final_distance(Particle a, Particle b) {
  double col_pos = collision(a, b);
  std::pair<double, double> after_col_vel = velocity_after_collision(a, b);
  double distA =
      sqrt(pow(a.get_position(), 2) + pow(collision_position(a, b), 2));
  double distB =
      sqrt(pow(b.get_position(), 2) + pow(collision_position(a, b), 2));
  Particle aac =
      Particle(a.get_mass(), collision_position(a, b), after_col_vel.first);
  Particle bac =
      Particle(b.get_mass(), collision_position(a, b), after_col_vel.second);
  return {distA + stop_distance_of(aac), distB + stop_distance_of(bac)};
}
