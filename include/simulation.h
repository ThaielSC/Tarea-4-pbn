#pragma once
#include "particle.h"

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
};
