#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "RTSNavigationLib/Pathfinding/DijkstraGrid.h"

namespace FlockTest {
  TEST_CASE("DijkstraGrid/singleStep", "[DijkstraGridSingleStep]") {
    glm::ivec2 resolution = glm::ivec2(3, 3);
    float t = 1; //target
    glm::ivec2 target = glm::ivec2(1, 1);

    std::vector<float> obstacles = {
      1,1,1,
      1,t,2,
      1,1,1,
    };
    RTSNavigationLib::DijkstraGrid grid(obstacles, resolution, target);
    
    REQUIRE(grid.getDistance(glm::ivec2(0, 0)) == 1);
    REQUIRE(grid.getDistance(glm::ivec2(1, 0)) == 1);
    REQUIRE(grid.getDistance(glm::ivec2(2, 0)) == 1);
    REQUIRE(grid.getDistance(glm::ivec2(0, 1)) == 1);
    REQUIRE(grid.getDistance(glm::ivec2(1, 1)) == 0);
    REQUIRE(grid.getDistance(glm::ivec2(2, 1)) == 2);
    REQUIRE(grid.getDistance(glm::ivec2(0, 2)) == 1);
    REQUIRE(grid.getDistance(glm::ivec2(1, 2)) == 1);
    REQUIRE(grid.getDistance(glm::ivec2(2, 2)) == 1);
  }
}