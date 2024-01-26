#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "RTSNavigationLib/Pathfinding/EikonalGrid.h"

namespace FlockTest {
  TEST_CASE("EikonalGrid/singleStep", "[EikonalGridSingleStep]") {
    glm::ivec2 resolution = glm::ivec2(3, 3);
    float t = 1; //target
    glm::ivec2 target = glm::ivec2(1, 1);

    std::vector<float> obstacles = {
      1,1,1,
      1,t,1,
      1,1,1,
    };
    RTSNavigationLib::EikonalGrid grid(obstacles, resolution, { target });
    
    REQUIRE(std::abs(grid.getDistance(glm::ivec2(0, 0)) - 1.70710683) < 1e-3);
    REQUIRE(std::abs(grid.getDistance(glm::ivec2(1, 0)) - 1         ) < 1e-3);
    REQUIRE(std::abs(grid.getDistance(glm::ivec2(2, 0)) - 1.70710683) < 1e-3);
    REQUIRE(std::abs(grid.getDistance(glm::ivec2(0, 1)) - 1         ) < 1e-3);
    REQUIRE(std::abs(grid.getDistance(glm::ivec2(1, 1)) - 0         ) < 1e-3);
    REQUIRE(std::abs(grid.getDistance(glm::ivec2(2, 1)) - 1         ) < 1e-3);
    REQUIRE(std::abs(grid.getDistance(glm::ivec2(0, 2)) - 1.70710683) < 1e-3);
    REQUIRE(std::abs(grid.getDistance(glm::ivec2(1, 2)) - 1         ) < 1e-3);
    REQUIRE(std::abs(grid.getDistance(glm::ivec2(2, 2)) - 1.70710683) < 1e-3);
  }

  TEST_CASE("EikonalGrid/tunnel", "[EikonalGridTunnel]") {
    glm::ivec2 resolution = glm::ivec2(10, 1);
    float t = 1; //target
    glm::ivec2 target = glm::ivec2(0, 0);

    std::vector<float> obstacles = {
      t,1,1,1,1,3,1,1,1,1
    };
    RTSNavigationLib::EikonalGrid grid(obstacles, resolution, { target });

    
    for (size_t i = 1; i < obstacles.size(); i++)
      REQUIRE(grid.getDistance(glm::ivec2(i - 1, 0)) < grid.getDistance(glm::ivec2(i, 0)));
  }

  TEST_CASE("EikonalGrid/obstacle", "[EikonalGridObstacle]") {
    glm::ivec2 resolution = glm::ivec2(3, 3);
    glm::ivec2 target = glm::ivec2(0, 1);

    float t = 1; //target
    constexpr float B = std::numeric_limits<float>::infinity();//obstacle
    std::vector<float> obstacles = {
      1,B,1,
      t,B,1,
      1,1,1,
    };
    RTSNavigationLib::EikonalGrid grid(obstacles, resolution, { target });

    std::vector<glm::ivec2> bestPath = { glm::ivec2(0,1),glm::ivec2(0,2),glm::ivec2(1,2),glm::ivec2(2,2),glm::ivec2(2,1),glm::ivec2(2,0) };

    for (size_t i = 1; i < bestPath.size(); i++)
      REQUIRE(grid.getDistance(bestPath[i-1]) < grid.getDistance(bestPath[i]));
  }
}