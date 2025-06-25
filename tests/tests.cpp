#include <utility>
#define CATCH_CONFIG_MAIN
#include "../include/simulation.h"
#include "catch.hpp"

TEST_CASE("Collision Example", "[Example][Collision]") {
  auto s = Simulation(0.2, 9.81);
  auto a = Particle(2, 0, 5);
  auto b = Particle(1, 10, -3);
  REQUIRE(s.collision(a, b) == true);
}

TEST_CASE("Collision_time Example", "[Example][Time]") {
  auto s = Simulation(0.2, 9.81);
  auto a = Particle(2, 0, 5);
  auto b = Particle(1, 10, -3);

  REQUIRE(s.collision_time(a, b) == Approx(1.25));
}

TEST_CASE("Collision_position Example", "[Example][Position]") {
  auto s = Simulation(0.2, 9.81);
  auto a = Particle(2, 0, 5);
  auto b = Particle(1, 10, -3);

  REQUIRE(s.collision_position(a, b) == Approx(4.7171875));
}

TEST_CASE("Velocity_after_collision Example", "[Example][Velocity]") {
  auto s = Simulation(0.2, 9.81);
  auto a = Particle(2, 0, 5);
  auto b = Particle(1, 10, -3);

  auto expected = std::make_pair(-0.3333333333, 7.6666666667);

  auto result = s.velocity_after_collision(a, b);

  REQUIRE(result.first == Approx(expected.first));
  REQUIRE(result.second == Approx(expected.second));
}

TEST_CASE("Final_distance Example", "[Example][Distance]") {
  auto s = Simulation(0.2, 9.81);
  auto a = Particle(2, 0, 5);
  auto b = Particle(1, 10, -3);

  REQUIRE(s.final_distance(a, b).first == Approx(0.0283).margin(0.001));
  REQUIRE(s.final_distance(a, b).second == Approx(14.979).margin(0.01));
}
