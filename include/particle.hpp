#pragma once
class Particle {
public:
  Particle(double mass, double init_pos, double init_vel);
  double get_mass();
  double get_position();
  double get_velocity();

private:
  double _mass;
  double _position;
  double _velocity;
};
