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
    
    REQUIRE(grid.getDistance(glm::ivec2(0, 0)) == 2);
    REQUIRE(grid.getDistance(glm::ivec2(1, 0)) == 1);
    REQUIRE(grid.getDistance(glm::ivec2(2, 0)) == 2);
    REQUIRE(grid.getDistance(glm::ivec2(0, 1)) == 1);
    REQUIRE(grid.getDistance(glm::ivec2(1, 1)) == 0);
    REQUIRE(grid.getDistance(glm::ivec2(2, 1)) == 2);
    REQUIRE(grid.getDistance(glm::ivec2(0, 2)) == 2);
    REQUIRE(grid.getDistance(glm::ivec2(1, 2)) == 1);
    REQUIRE(grid.getDistance(glm::ivec2(2, 2)) == 2);
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
      1,B,1,    //1,B,5
      t,B,1,//->//0,B,4
      1,1,1,    //1,2,3
    };
    RTSNavigationLib::DijkstraGrid grid(obstacles, resolution, { target });

    
    REQUIRE(grid.getDistance(glm::ivec2(0, 0)) == 1);
    REQUIRE(grid.getDistance(glm::ivec2(1, 0)) == B);
    REQUIRE(grid.getDistance(glm::ivec2(2, 0)) == 5);
    REQUIRE(grid.getDistance(glm::ivec2(0, 1)) == 0);
    REQUIRE(grid.getDistance(glm::ivec2(1, 1)) == B);
    REQUIRE(grid.getDistance(glm::ivec2(2, 1)) == 4);
    REQUIRE(grid.getDistance(glm::ivec2(0, 2)) == 1);
    REQUIRE(grid.getDistance(glm::ivec2(1, 2)) == 2);
    REQUIRE(grid.getDistance(glm::ivec2(2, 2)) == 3);
  }

  TEST_CASE("DijkstraGrid/TwoPath", "[DijkstraGridObstacle]") {
    glm::ivec2 resolution = glm::ivec2(3, 4);
    glm::ivec2 target = glm::ivec2(2, 1);

    float t = 1; //target
    constexpr float B = std::numeric_limits<float>::infinity();//obstacle
    std::vector<float> obstacles = {
      1,5,1,//     7,6,1
      1,B,t,// ->  6,B,0
      1,B,1,//     5,B,1
      1,1,1,//     4,3,2
    };
    RTSNavigationLib::DijkstraGrid grid(obstacles, resolution, { target });

    REQUIRE(grid.getDistance(glm::ivec2(0, 0)) == 7);
    REQUIRE(grid.getDistance(glm::ivec2(1, 0)) == 6);
    REQUIRE(grid.getDistance(glm::ivec2(2, 0)) == 1);
    REQUIRE(grid.getDistance(glm::ivec2(0, 1)) == 6);
    REQUIRE(grid.getDistance(glm::ivec2(1, 1)) == B);
    REQUIRE(grid.getDistance(glm::ivec2(2, 1)) == 0);
    REQUIRE(grid.getDistance(glm::ivec2(0, 2)) == 5);
    REQUIRE(grid.getDistance(glm::ivec2(1, 2)) == B);
    REQUIRE(grid.getDistance(glm::ivec2(2, 2)) == 1);
    REQUIRE(grid.getDistance(glm::ivec2(0, 3)) == 4);
    REQUIRE(grid.getDistance(glm::ivec2(1, 3)) == 3);
    REQUIRE(grid.getDistance(glm::ivec2(2, 3)) == 2);
  }

  TEST_CASE("DijkstraGrid/Horizon", "[DijkstralEdge]") {
    glm::ivec2 resolution = glm::ivec2(5, 5);
    glm::ivec2 start = glm::ivec2(1, 1);
    std::vector<glm::ivec2> targets = { glm::ivec2(0,0), glm::ivec2(1,0), glm::ivec2(2,0), glm::ivec2(3,0), glm::ivec2(4,0) };
    float t = 1; //target
    float s = 1; //start
    std::vector<float> obstacles = {
      t,t,t,t,t,
      1,1,1,1,1,
      1,1,1,1,1,
      1,1,s,1,1,
      1,1,1,1,1
    };
    RTSNavigationLib::DijkstraGrid grid(obstacles, resolution, targets);

    for (size_t i = 0; i < 5; i++)
      REQUIRE(grid.getDistance(i) == 0);
    for (size_t i = 5; i < 10; i++)
      REQUIRE(grid.getDistance(i) == 1);
    for (size_t i = 10; i < 15; i++)
      REQUIRE(grid.getDistance(i) == 2);
    for (size_t i = 15; i < 20; i++)
      REQUIRE(grid.getDistance(i) == 3);
    for (size_t i = 20; i < 25; i++)
      REQUIRE(grid.getDistance(i) == 4);
  }
}