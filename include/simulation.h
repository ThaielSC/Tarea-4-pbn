#include "particle.h"

class Simulation {
private:
  double mu;
  double g;

public:
  Simulation(double coef_friction, double gravity);
  /* Calcula la energía de una particula en un instante t */
  double energy_of(Particle, double t);
  /* Calcula la velocidad de una particula en un instante t */
  double velocity_of(Particle, double t);
  /* Calcula la distancia de detención de una particula */
  double stop_distance_of(Particle);
  /* Determina si 2 particulas colisionan */
  bool collision(Particle, Particle);
};
