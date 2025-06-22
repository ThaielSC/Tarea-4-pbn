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
  REQUIRE(s.collision_time(a, b) == 1.25);
}

TEST_CASE("Collision_position Example", "[Example][Position]") {
  auto s = Simulation(0.2, 9.81);
  auto a = Particle(2, 0, 5);
  auto b = Particle(1, 10, -3);
  REQUIRE(s.collision_position(a, b) == 4.7171875);
}

// TEST_CASE("Velocity_before_collision Example", "[Example][Velocity]") {
//   auto s = Simulation(0.2, 9.81);
//   auto a = Particle(2, 0, 5);
//   auto b = Particle(1, 10, -3);
//   REQUIRE(s.velocity_after_collision(a, b) == {-0.33, 7.66});
// }

// TEST_CASE("Final_distance Example", "[Example][Collision]") {
//   auto s = Simulation(0.2, 9.81);
//   auto a = Particle(2, 0, 5);
//   auto b = Particle(1, 10, -3);
//   REQUIRE(s.final_distance(a, b) == {0.0283,14.953});
// }
