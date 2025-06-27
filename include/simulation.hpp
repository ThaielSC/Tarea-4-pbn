#pragma once
#include "particle.hpp"
#include <utility>

class Simulation {
private:
  double mu;
  double g;

  double particles_distance(Particle a, Particle b);

public:
  Simulation(double coef_friction, double gravity);
  /* Calcula la distancia de detención de una particula */
  double stop_distance_of(Particle);
  /* Determina si 2 particulas colisionan */
  bool collision(Particle, Particle);
  /* Calcula el tiempo de colisión entre dos partículas */
  double collision_time(Particle, Particle);

  double collision_position(Particle a, Particle b);

  std::pair<double, double> velocity_after_collision(Particle a, Particle b);

  std::pair<double, double> final_distance(Particle a, Particle b);
};
