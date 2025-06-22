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

template <typename T> int sign(T num) { return (T(0) < num) - (num < T(0)); }

std::pair<double, double> Simulation::final_distance(Particle a, Particle b) {
  double collision_pos = collision_position(a, b);
  std::pair<double, double> collision_vel = velocity_after_collision(a, b);
  std::pair<double, double> after_col_dist = {
      stop_distance_of(
          Particle(a.get_mass(), collision_pos, collision_vel.first)),
      stop_distance_of(
          Particle(b.get_mass(), collision_pos, collision_vel.second))};
  std::pair<double, double> end_positions = {
      collision_pos + sign(collision_vel.first) * after_col_dist.first,
      collision_pos + sign(collision_vel.second) * after_col_dist.second};
  std::pair<double, double> final_dist = {
      fabs(end_positions.first - a.get_position()),
      fabs(end_positions.second - b.get_position())};
  return final_dist;
}
