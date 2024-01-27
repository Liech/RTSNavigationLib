#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "RTSNavigationLib/Pathfinding/FlowField.h"
#include "RTSNavigationLib/Pathfinding/EikonalGrid.h"
#include "RTSNavigationLib/Pathfinding/DijkstraGrid.h"

namespace FlockTest {

  TEST_CASE("FlowField/Dijkstra/Horizon", "[DijkstralEdge]") {
    glm::ivec2 resolution = glm::ivec2(5, 5);
    glm::ivec2 start = glm::ivec2(2, 3);
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
    RTSNavigationLib::FlowField field(grid);


    for (size_t x = 0; x < 5; x++) {
      for (size_t y = 1; y < 5; y++) {
        glm::dvec2 dir = field.getDirection(glm::ivec2(x,y));
        REQUIRE(dir[0] == 0);
        REQUIRE(dir[1] == -1);
      }
    }
  }

  TEST_CASE("FlowField/Eikonal/Horizon", "[DijkstralEdge]") {
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
    RTSNavigationLib::EikonalGrid grid(obstacles, resolution, targets);
    RTSNavigationLib::FlowField field(grid);

    glm::dvec2 dir = field.getDirection(start);
    REQUIRE(dir[0] == 0);
    REQUIRE(dir[1] == -1);
  }

  TEST_CASE("FlowField/Dijkstra/Edge", "[DijkstralEdge]") {
    glm::ivec2 resolution = glm::ivec2(4, 4);
    glm::ivec2 start = glm::ivec2(1, 1);
    glm::ivec2 target = glm::ivec2(2, 2);
    glm::ivec2 wall = glm::ivec2(2, 1);
    float t = 1; //target
    float s = 1; //start
    float B = std::numeric_limits<float>::infinity();
    std::vector<float> obstacles = {
      1,1,1,1,
      1,s,B,1,
      1,1,t,1,
      1,1,1,1,
    };
    RTSNavigationLib::DijkstraGrid grid(obstacles, resolution, { target });
    RTSNavigationLib::FlowField field(grid);

    auto dir       = field.getDirection(start);
    auto targetDir = field.getDirection(target);
    auto wallDir   = field.getDirection(wall);

    REQUIRE(dir[0] == 0);
    REQUIRE(dir[1] == 1);
    REQUIRE(targetDir[0] == 0);
    REQUIRE(targetDir[1] == 0);
    REQUIRE(wallDir[0] == 0);
    REQUIRE(wallDir[1] == 0);

  }
  TEST_CASE("FlowField/Eikonal/Edge", "[EikonalEdge]") {
    glm::ivec2 resolution = glm::ivec2(4, 4);
    glm::ivec2 start = glm::ivec2(1, 1);
    glm::ivec2 target = glm::ivec2(2, 2);
    glm::ivec2 wall = glm::ivec2(2, 1);
    float t = 1; //target
    float s = 1; //start
    float B = std::numeric_limits<float>::infinity();
    std::vector<float> obstacles = {
      1,1,1,1,
      1,s,B,1,
      1,1,t,1,
      1,1,1,1,
    };
    RTSNavigationLib::EikonalGrid grid(obstacles, resolution, { target });
    RTSNavigationLib::FlowField field(grid);

    auto dir       = field.getDirection(start);
    auto targetDir = field.getDirection(target);
    auto wallDir   = field.getDirection(wall);

    REQUIRE(dir[0] == 0);
    REQUIRE(dir[1] == 1);
    REQUIRE(targetDir[0] == 0);
    REQUIRE(targetDir[1] == 0);
    REQUIRE(wallDir[0] == 0);
    REQUIRE(wallDir[1] == 0);
  }

  TEST_CASE("FlowField/Eikonal/Simple", "[EikonalSimpleSingleStep]") {
    glm::ivec2 resolution = glm::ivec2(5, 5);
    glm::ivec2 fromA = glm::ivec2(1+0, 1+1);
    glm::ivec2 fromB = glm::ivec2(1+1, 1+0);
    glm::ivec2 fromC = glm::ivec2(1+2, 1+1);
    glm::ivec2 fromD = glm::ivec2(1+1, 1+2);
    glm::ivec2 fromE = glm::ivec2(1+0, 1+0);
    glm::ivec2 fromF = glm::ivec2(1+2, 1+0);
    glm::ivec2 fromG = glm::ivec2(1+0, 1+2);
    glm::ivec2 fromH = glm::ivec2(1+2, 1+2);
    glm::ivec2 target= glm::ivec2(1+1, 1+1);

    float t = 1; //target
    float a = 1; float b = 1; float c = 1; float d = 1; float e = 1; float f = 1; float g = 1; float h = 1; // for visualization
    std::vector<float> obstacles = {
      1,1,1,1,1,
      1,e,b,f,1,
      1,a,t,c,1,
      1,g,d,h,1,
      1,1,1,1,1
    };
      
    RTSNavigationLib::EikonalGrid grid(obstacles, resolution, { target });
    RTSNavigationLib::FlowField field(grid);
    glm::dvec2 directionA = field.getDirection(fromA);
    glm::dvec2 directionB = field.getDirection(fromB);
    glm::dvec2 directionC = field.getDirection(fromC);
    glm::dvec2 directionD = field.getDirection(fromD);
    glm::dvec2 directionE = field.getDirection(fromE);
    glm::dvec2 directionF = field.getDirection(fromF);
    glm::dvec2 directionG = field.getDirection(fromG);
    glm::dvec2 directionH = field.getDirection(fromH);

    REQUIRE(directionA[0] == glm::dvec2(1, 0)[0]);
    REQUIRE(directionA[1] == glm::dvec2(1, 0)[1]);
    REQUIRE(directionB[0] == glm::dvec2(0, 1)[0]);
    REQUIRE(directionB[1] == glm::dvec2(0, 1)[1]);
    REQUIRE(directionC[0] == glm::dvec2(-1, 0)[0]);
    REQUIRE(directionC[1] == glm::dvec2(-1, 0)[1]);
    REQUIRE(directionD[0] == glm::dvec2(0, -1)[0]);
    REQUIRE(directionD[1] == glm::dvec2(0, -1)[1]);

    REQUIRE(std::abs(directionE[0] - glm::normalize(glm::dvec2(1, 1))[0]) < 1e-6);
    REQUIRE(std::abs(directionE[1] - glm::normalize(glm::dvec2(1, 1))[1]) < 1e-6);
    REQUIRE(std::abs(directionF[0] - glm::normalize(glm::dvec2(-1, 1))[0]) < 1e-6);
    REQUIRE(std::abs(directionF[1] - glm::normalize(glm::dvec2(-1, 1))[1]) < 1e-6);
    REQUIRE(std::abs(directionG[0] - glm::normalize(glm::dvec2(1, -1))[0]) < 1e-6);
    REQUIRE(std::abs(directionG[1] - glm::normalize(glm::dvec2(1, -1))[1]) < 1e-6);
    REQUIRE(std::abs(directionH[0] - glm::normalize(glm::dvec2(-1, -1))[0]) < 1e-6);
    REQUIRE(std::abs(directionH[1] - glm::normalize(glm::dvec2(-1, -1))[1]) < 1e-6);
  }
  TEST_CASE("FlowField/Dijkstra/Simple", "[DijkstraSimpleSingleStep]") {
    glm::ivec2 resolution = glm::ivec2(5, 5);
    glm::ivec2 fromA = glm::ivec2(1 + 0, 1 + 1);
    glm::ivec2 fromB = glm::ivec2(1 + 1, 1 + 0);
    glm::ivec2 fromC = glm::ivec2(1 + 2, 1 + 1);
    glm::ivec2 fromD = glm::ivec2(1 + 1, 1 + 2);
    glm::ivec2 fromE = glm::ivec2(1 + 0, 1 + 0);
    glm::ivec2 fromF = glm::ivec2(1 + 2, 1 + 0);
    glm::ivec2 fromG = glm::ivec2(1 + 0, 1 + 2);
    glm::ivec2 fromH = glm::ivec2(1 + 2, 1 + 2);
    glm::ivec2 target = glm::ivec2(1 + 1, 1 + 1);

    float t = 1; //target
    float a = 1; float b = 1; float c = 1; float d = 1; float e = 1; float f = 1; float g = 1; float h = 1; // for visualization
    std::vector<float> obstacles = {
      1,1,1,1,1,
      1,e,b,f,1,
      1,a,t,c,1,
      1,g,d,h,1,
      1,1,1,1,1
    };

    RTSNavigationLib::DijkstraGrid grid(obstacles, resolution, { target });
    RTSNavigationLib::FlowField field(grid);
    glm::dvec2 directionA = field.getDirection(fromA);
    glm::dvec2 directionB = field.getDirection(fromB);
    glm::dvec2 directionC = field.getDirection(fromC);
    glm::dvec2 directionD = field.getDirection(fromD);
    glm::dvec2 directionE = field.getDirection(fromE);
    glm::dvec2 directionF = field.getDirection(fromF);
    glm::dvec2 directionG = field.getDirection(fromG);
    glm::dvec2 directionH = field.getDirection(fromH);

    REQUIRE(directionA[0] == glm::dvec2(1, 0)[0]);
    REQUIRE(directionA[1] == glm::dvec2(1, 0)[1]);
    REQUIRE(directionB[0] == glm::dvec2(0, 1)[0]);
    REQUIRE(directionB[1] == glm::dvec2(0, 1)[1]);
    REQUIRE(directionC[0] == glm::dvec2(-1, 0)[0]);
    REQUIRE(directionC[1] == glm::dvec2(-1, 0)[1]);
    REQUIRE(directionD[0] == glm::dvec2(0, -1)[0]);
    REQUIRE(directionD[1] == glm::dvec2(0, -1)[1]);

    REQUIRE(std::abs(directionE[0] - glm::normalize(glm::dvec2(1, 1))[0]) < 1e-6);
    REQUIRE(std::abs(directionE[1] - glm::normalize(glm::dvec2(1, 1))[1]) < 1e-6);
    REQUIRE(std::abs(directionF[0] - glm::normalize(glm::dvec2(-1, 1))[0]) < 1e-6);
    REQUIRE(std::abs(directionF[1] - glm::normalize(glm::dvec2(-1, 1))[1]) < 1e-6);
    REQUIRE(std::abs(directionG[0] - glm::normalize(glm::dvec2(1, -1))[0]) < 1e-6);
    REQUIRE(std::abs(directionG[1] - glm::normalize(glm::dvec2(1, -1))[1]) < 1e-6);
    REQUIRE(std::abs(directionH[0] - glm::normalize(glm::dvec2(-1, -1))[0]) < 1e-6);
    REQUIRE(std::abs(directionH[1] - glm::normalize(glm::dvec2(-1, -1))[1]) < 1e-6);
  }
}