#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "RTSNavigationLib/Flocking/Flock.h"
#include "RTSNavigationLib/Flocking/Boid.h"

namespace FlockTest {
  TEST_CASE("Flocking/base", "[FlockingBase]") {
    RTSPathingLib::Flock flock(glm::dvec2(20, 20), 3);
    auto pos = glm::dvec2(3, 3);
    auto dir = glm::dvec2(1, 0);
    auto boid = flock.createBoid(pos, dir, 1);

    flock.calculateForces();

    REQUIRE(boid->position[0] == pos[0]);
    REQUIRE(boid->position[1] == pos[1]);
    REQUIRE(boid->velocity[0] == dir[0]);
    REQUIRE(boid->velocity[1] == dir[1]);
  }

  TEST_CASE("Flocking/OnlyOne", "[FlockingSingle]") {
    RTSPathingLib::Flock flock(glm::dvec2(20, 20), 3);
    auto pos = glm::dvec2(3, 3);
    auto dir = glm::dvec2(1, 0);
    auto boid = flock.createBoid(pos, dir, 1);

    flock.calculateForces();

    auto cohesion = boid->getCohesionForce();
    REQUIRE(cohesion[0] == 0);
    REQUIRE(cohesion[1] == 0);

    auto seperation = boid->getSeperationForce();
    REQUIRE(seperation[0] == 0);
    REQUIRE(seperation[1] == 0);

    auto alignment = boid->getAlignmentForce();
    REQUIRE(alignment[0] == 0);
    REQUIRE(alignment[1] == 0);
  }

  TEST_CASE("Flocking/OutOfReach", "[FlockingOutOfReach]") {
    RTSPathingLib::Flock flock(glm::dvec2(20, 20), 3);
    auto pos1 = glm::dvec2(3, 3);
    auto dir1 = glm::dvec2(1, 0);
    auto pos2 = glm::dvec2(7, 2.2);
    auto dir2 = glm::normalize(glm::dvec2(0.4, -0.3));

    auto boid1 = flock.createBoid(pos1, dir1, 1);
    auto boid2 = flock.createBoid(pos2, dir2, 1);
    flock.calculateForces();

    auto cohesion1 = boid1->getCohesionForce();
    auto cohesion2 = boid2->getCohesionForce();
    REQUIRE(cohesion1[0] == 0);
    REQUIRE(cohesion1[1] == 0);
    REQUIRE(cohesion2[0] == 0);
    REQUIRE(cohesion2[1] == 0);

    auto seperation1 = boid1->getSeperationForce();
    auto seperation2 = boid2->getSeperationForce();
    REQUIRE(seperation1[0] == 0);
    REQUIRE(seperation1[1] == 0);
    REQUIRE(seperation2[0] == 0);
    REQUIRE(seperation2[1] == 0);

    auto alignment1 = boid1->getAlignmentForce();
    auto alignment2 = boid2->getAlignmentForce();
    REQUIRE(alignment1[0] == 0);
    REQUIRE(alignment1[1] == 0);
    REQUIRE(alignment2[0] == 0);
    REQUIRE(alignment2[1] == 0);
  }

  TEST_CASE("Flocking/SeperationTwo", "[FlockingSeperationTwo]") {
    RTSPathingLib::Flock flock(glm::dvec2(20, 20), 3);
    auto pos1 = glm::dvec2(3, 3);
    auto dir1 = glm::dvec2(1, 0);
    auto pos2 = glm::dvec2(0.5, 2.2);
    auto dir2 = glm::normalize(glm::dvec2(0.4, -0.3));

    auto boid1 = flock.createBoid(pos1, dir1, 1);
    auto boid2 = flock.createBoid(pos2, dir2, 1);
    flock.calculateForces();

    auto seperation1 = boid1->getSeperationForce();
    auto seperation2 = boid2->getSeperationForce();
    auto boid2boid = glm::normalize(pos1 - pos2);
    REQUIRE_THAT(seperation1[0] -  boid2boid[0] == 0, Catch::Matchers::WithinAbs(0, 0.000001));
    REQUIRE_THAT(seperation1[1] -  boid2boid[1] == 0, Catch::Matchers::WithinAbs(0, 0.000001));
    REQUIRE_THAT(seperation2[0] - -boid2boid[0] == 0, Catch::Matchers::WithinAbs(0, 0.000001));
    REQUIRE_THAT(seperation2[1] - -boid2boid[1] == 0, Catch::Matchers::WithinAbs(0, 0.000001));
  }

  TEST_CASE("Flocking/CohesionTwo", "[FlockingCohesionTwo]") {
    RTSPathingLib::Flock flock(glm::dvec2(20, 20), 3);
    auto pos1 = glm::dvec2(6, 2);
    auto dir1 = glm::normalize(glm::dvec2(0.7, 0.3));
    auto pos2 = glm::dvec2(6.7, 5);
    auto dir2 = glm::normalize(glm::dvec2(0.4, -0.3));

    auto boid1 = flock.createBoid(pos1, dir1, 1);
    auto boid2 = flock.createBoid(pos2, dir2, 1);
    flock.calculateForces();

    auto cohesion1 = boid1->getCohesionForce();
    auto cohesion2 = boid2->getCohesionForce();
    auto boid2boid = glm::normalize(pos1 - pos2);
    REQUIRE_THAT(cohesion1[0] - -boid2boid[0] == 0, Catch::Matchers::WithinAbs(0, 0.000001));
    REQUIRE_THAT(cohesion1[1] - -boid2boid[1] == 0, Catch::Matchers::WithinAbs(0, 0.000001));
    REQUIRE_THAT(cohesion2[0] -  boid2boid[0] == 0, Catch::Matchers::WithinAbs(0, 0.000001));
    REQUIRE_THAT(cohesion2[1] -  boid2boid[1] == 0, Catch::Matchers::WithinAbs(0, 0.000001));
  }

  TEST_CASE("Flocking/AlignmentTwo", "[FlockingAlginmentTwo]") {
    RTSPathingLib::Flock flock(glm::dvec2(20, 20), 3);
    auto pos1 = glm::dvec2(6, 3);
    auto dir1 = glm::normalize(glm::dvec2(0.7, 0.3));
    auto pos2 = glm::dvec2(6.7, 5);
    auto dir2 = glm::normalize(glm::dvec2(0.4, -0.3));

    auto boid1 = flock.createBoid(pos1, dir1, 1);
    auto boid2 = flock.createBoid(pos2, dir2, 1);
    flock.calculateForces();

    auto alignment1 = boid1->getAlignmentForce();
    auto alignment2 = boid2->getAlignmentForce();
    auto dir2dir = glm::normalize(dir1 - dir2);
    REQUIRE_THAT(alignment1[0] - -dir2dir[0] == 0, Catch::Matchers::WithinAbs(0, 0.000001));
    REQUIRE_THAT(alignment1[1] - -dir2dir[1] == 0, Catch::Matchers::WithinAbs(0, 0.000001));
    REQUIRE_THAT(alignment2[0] -  dir2dir[0] == 0, Catch::Matchers::WithinAbs(0, 0.000001));
    REQUIRE_THAT(alignment2[1] -  dir2dir[1] == 0, Catch::Matchers::WithinAbs(0, 0.000001));
  }
}