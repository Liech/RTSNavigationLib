#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "RTSNavigationLib/Pathfinding/FlowField.h"

namespace FlockTest {
  TEST_CASE("FlowField/singleStep", "[FlowFieldSingleStep]") {
    glm::ivec2 resolution = glm::ivec2(3, 3);
    float t = 0; //target
    float a = 0; //for visualization purposes
    float b = 0; //for visualization purposes
    float c = 0; //for visualization purposes
    float d = 0; //for visualization purposes
    glm::ivec2 fromA = glm::ivec2(0, 1);
    glm::ivec2 fromB = glm::ivec2(1, 0);
    glm::ivec2 fromC = glm::ivec2(2, 1);
    glm::ivec2 fromD = glm::ivec2(1, 2);
    glm::ivec2 target= glm::ivec2(1, 1);

    std::vector<float> obstacles = {
      0,b,0,
      a,t,c,
      0,d,0 
    };
      
    RTSNavigationLib::FlowField field(obstacles, resolution, target);
    glm::dvec2 directionA = field.getDirection(fromA);
    glm::dvec2 directionB = field.getDirection(fromB);
    glm::dvec2 directionC = field.getDirection(fromC);
    glm::dvec2 directionD = field.getDirection(fromD);

    REQUIRE(directionA.x ==  1);
    REQUIRE(directionA.y ==  0);
    REQUIRE(directionB.x ==  0);
    REQUIRE(directionB.y ==  1);
    REQUIRE(directionC.x == -1);
    REQUIRE(directionC.y ==  0);
    REQUIRE(directionD.x ==  0);
    REQUIRE(directionD.y == -1);
  }
}