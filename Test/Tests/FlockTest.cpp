#include <catch2/catch_test_macros.hpp>

#include "RTSNavigationLib/Flocking/Flock.h"
#include "RTSNavigationLib/Flocking/Boid.h"

namespace FlockTest {
  TEST_CASE("Flocking/base", "[FlockingBase]") {
    RTSPathingLib::Flock flock(glm::dvec2(20, 20), 3);
    auto pos = glm::dvec2(3, 3);
    auto dir = glm::dvec2(1, 0);
    auto boid = flock.createBoid(pos, dir, 1);
    REQUIRE(boid->position[0] == pos[0]);
    REQUIRE(boid->position[1] == pos[1]);
    REQUIRE(boid->velocity[0] == dir[0]);
    REQUIRE(boid->velocity[1] == dir[1]);
  }
}