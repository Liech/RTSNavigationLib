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
    RTSNavigationLib::DijkstraGrid grid(obstacles, resolution, { target });
    
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

  TEST_CASE("DijkstraGrid/tunnel", "[DijkstraGridTunnel]") {
    glm::ivec2 resolution = glm::ivec2(10, 1);
    float t = 1; //target
    glm::ivec2 target = glm::ivec2(0, 0);

    std::vector<float> obstacles = {
      t,1,1,1,1,3,1,1,1,1
    };
    RTSNavigationLib::DijkstraGrid grid(obstacles, resolution, { target });

    REQUIRE(grid.getDistance(glm::ivec2(0, 0)) == 0 );
    REQUIRE(grid.getDistance(glm::ivec2(1, 0)) == 1 );
    REQUIRE(grid.getDistance(glm::ivec2(2, 0)) == 2 );
    REQUIRE(grid.getDistance(glm::ivec2(3, 0)) == 3 );
    REQUIRE(grid.getDistance(glm::ivec2(4, 0)) == 4 );
    REQUIRE(grid.getDistance(glm::ivec2(5, 0)) == 7 );
    REQUIRE(grid.getDistance(glm::ivec2(6, 0)) == 8 );
    REQUIRE(grid.getDistance(glm::ivec2(7, 0)) == 9 );
    REQUIRE(grid.getDistance(glm::ivec2(8, 0)) == 10);
    REQUIRE(grid.getDistance(glm::ivec2(9, 0)) == 11);
  }

  TEST_CASE("DijkstraGrid/obstacle", "[DijkstraGridObstacle]") {
    glm::ivec2 resolution = glm::ivec2(3, 3);
    glm::ivec2 target = glm::ivec2(0, 1);

    float t = 1; //target
    constexpr float B = std::numeric_limits<float>::infinity();//obstacle
    std::vector<float> obstacles = {
      1,B,1,    //1,B,3
      t,B,1,//->//0,B,2
      1,1,1,    //1,1,2 // remember: diagonal movement is possible
    };
    RTSNavigationLib::DijkstraGrid grid(obstacles, resolution, { target });

    
    REQUIRE(grid.getDistance(glm::ivec2(0, 0)) == 1);
    REQUIRE(grid.getDistance(glm::ivec2(1, 0)) == B);
    REQUIRE(grid.getDistance(glm::ivec2(2, 0)) == 3);
    REQUIRE(grid.getDistance(glm::ivec2(0, 1)) == 0);
    REQUIRE(grid.getDistance(glm::ivec2(1, 1)) == B);
    REQUIRE(grid.getDistance(glm::ivec2(2, 1)) == 2);
    REQUIRE(grid.getDistance(glm::ivec2(0, 2)) == 1);
    REQUIRE(grid.getDistance(glm::ivec2(1, 2)) == 1);
    REQUIRE(grid.getDistance(glm::ivec2(2, 2)) == 2);
  }

  TEST_CASE("DijkstraGrid/TwoPath", "[DijkstraGridObstacle]") {
    glm::ivec2 resolution = glm::ivec2(3, 4);
    glm::ivec2 target = glm::ivec2(2, 1);

    float t = 1; //target
    constexpr float B = std::numeric_limits<float>::infinity();//obstacle
    std::vector<float> obstacles = {
      1,5,1,//     5,5,1
      1,B,t,// ->  4,B,0
      1,B,1,//     3,B,1
      1,1,1,//     3,2,2
    };
    RTSNavigationLib::DijkstraGrid grid(obstacles, resolution, { target });

    REQUIRE(grid.getDistance(glm::ivec2(0, 0)) == 5);
    REQUIRE(grid.getDistance(glm::ivec2(1, 0)) == 5);
    REQUIRE(grid.getDistance(glm::ivec2(2, 0)) == 1);
    REQUIRE(grid.getDistance(glm::ivec2(0, 1)) == 4);
    REQUIRE(grid.getDistance(glm::ivec2(1, 1)) == B);
    REQUIRE(grid.getDistance(glm::ivec2(2, 1)) == 0);
    REQUIRE(grid.getDistance(glm::ivec2(0, 2)) == 3);
    REQUIRE(grid.getDistance(glm::ivec2(1, 2)) == B);
    REQUIRE(grid.getDistance(glm::ivec2(2, 2)) == 1);
    REQUIRE(grid.getDistance(glm::ivec2(0, 3)) == 3);
    REQUIRE(grid.getDistance(glm::ivec2(1, 3)) == 2);
    REQUIRE(grid.getDistance(glm::ivec2(2, 3)) == 2);
  }
}