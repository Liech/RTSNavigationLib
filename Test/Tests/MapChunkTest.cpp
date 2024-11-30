#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "RTSNavigationLib/Pathfinding/FlowField.h"
#include "RTSNavigationLib/Pathfinding/MapChunk.h"
#include "RTSNavigationLib/Pathfinding/EikonalGrid.h"
#include "RTSNavigationLib/Pathfinding/DijkstraGrid.h"

namespace FlockTest {
  TEST_CASE("MapChunk/InputCheck") {
    glm::ivec2 resolution = glm::ivec2(3, 3);
    std::vector<float> obstacles = {
      1,1,1,
      1,1,1,
      1,1,1,
    };
    RTSNavigationLib::MapChunk chunk(obstacles, resolution, true);
    REQUIRE(chunk.getResolution() == resolution);
    REQUIRE(chunk.getObstacles() == obstacles);
  }

  TEST_CASE("MapChunk/PortalCount") {
    glm::ivec2 resolution = glm::ivec2(4, 4);
    constexpr float B = std::numeric_limits<float>::infinity();
    std::vector<float> obstacles = {
      1,1,1,1,
      1,1,1,1,
      1,1,1,B,
      B,B,1,1
    };
    RTSNavigationLib::MapChunk chunk(obstacles, resolution, true);
    REQUIRE(chunk.numberPortals(RTSNavigationLib::MajorDirection2D::Bot  ) == 1);
    REQUIRE(chunk.numberPortals(RTSNavigationLib::MajorDirection2D::Top  ) == 1);
    REQUIRE(chunk.numberPortals(RTSNavigationLib::MajorDirection2D::Left ) == 1);
    REQUIRE(chunk.numberPortals(RTSNavigationLib::MajorDirection2D::Right) == 2);
  }

  //TEST_CASE("MapChunk/GetMap/Eikonal") {
  //  glm::ivec2 resolution = glm::ivec2(4, 4);
  //  constexpr float B = std::numeric_limits<float>::infinity();
  //  float t = 1;
  //  std::vector<glm::ivec2> targets = { glm::ivec2(2,3),glm::ivec2(3,3) };
  //  std::vector<float> obstacles = {
  //    1,1,1,1,
  //    1,1,1,1,
  //    1,1,1,B,
  //    B,B,t,t
  //  };
  //  RTSNavigationLib::MapChunk chunk(obstacles, resolution, true);
  //  auto& map = chunk.getMap(RTSNavigationLib::MajorDirection2D::Bot,0);
  //  RTSNavigationLib::EikonalGrid grid(obstacles, resolution, targets);
  //  RTSNavigationLib::FlowField flow(grid);

  //  for (size_t x = 0; x < resolution.x; x++)
  //    for (size_t y = 0; y < resolution.y; y++)
  //      REQUIRE(flow.getDirection(glm::ivec2(x, y)) == map.getDirection(glm::ivec2(x, y)));
  //}

  //TEST_CASE("MapChunk/GetMap/Dijkstra") {
  //  glm::ivec2 resolution = glm::ivec2(4, 4);
  //  constexpr float B = std::numeric_limits<float>::infinity();
  //  float t = 1;
  //  std::vector<glm::ivec2> targets = { glm::ivec2(2,3),glm::ivec2(3,3) };
  //  std::vector<float> obstacles = {
  //    1,1,1,1,
  //    1,1,1,1,
  //    1,1,1,B,
  //    B,B,t,t
  //  };
  //  RTSNavigationLib::MapChunk chunk(obstacles, resolution, false);
  //  auto& map = chunk.getMap(RTSNavigationLib::MajorDirection2D::Bot, 0);
  //  RTSNavigationLib::DijkstraGrid grid(obstacles, resolution, targets);
  //  RTSNavigationLib::FlowField flow(grid);

  //  for (size_t x = 0; x < resolution.x; x++)
  //    for (size_t y = 0; y < resolution.y; y++)
  //      REQUIRE(flow.getDirection(glm::ivec2(x, y)) == map.getDirection(glm::ivec2(x, y)));
  //}

  //TEST_CASE("MapChunk/GetTraverseCost/BaseTunnel") {
  //  glm::ivec2 resolution = glm::ivec2(3, 3);
  //  constexpr float B = std::numeric_limits<float>::infinity();
  //  std::vector<float> obstacles = {
  //    B,1,B,
  //    B,1,B,
  //    B,1,B,
  //  };
  //  RTSNavigationLib::MapChunk chunk(obstacles, resolution, true);
  //  RTSNavigationLib::MapChunk chunkD(obstacles, resolution, false);
  //  float costUp    = chunk.getTraverseCost(RTSNavigationLib::MajorDirection2D::Bot, 0, RTSNavigationLib::MajorDirection2D::Top, 0);
  //  float costDown  = chunk.getTraverseCost(RTSNavigationLib::MajorDirection2D::Top, 0, RTSNavigationLib::MajorDirection2D::Bot, 0);
  //  float costUpD   = chunkD.getTraverseCost(RTSNavigationLib::MajorDirection2D::Bot, 0, RTSNavigationLib::MajorDirection2D::Top, 0);
  //  float costDownD = chunkD.getTraverseCost(RTSNavigationLib::MajorDirection2D::Top, 0, RTSNavigationLib::MajorDirection2D::Bot, 0);

  //  REQUIRE(chunk.numberPortals(RTSNavigationLib::MajorDirection2D::Left) == 0);
  //  REQUIRE(chunk.numberPortals(RTSNavigationLib::MajorDirection2D::Right) == 0);
  //  REQUIRE(chunk.numberPortals(RTSNavigationLib::MajorDirection2D::Bot) == 1);
  //  REQUIRE(chunk.numberPortals(RTSNavigationLib::MajorDirection2D::Top) == 1);

  //  REQUIRE(costUp   == 2);
  //  REQUIRE(costDown == 2);
  //  REQUIRE(costUpD  == 2);
  //  REQUIRE(costDownD== 2);
  //}

  TEST_CASE("MapChunk/GetTraverseCost/Edge") {
    glm::ivec2 resolution = glm::ivec2(3, 3);
    constexpr float B = std::numeric_limits<float>::infinity();
    float t = 1; //target
    std::vector<float> obstacles = {
      B,t,B,
      1,1,B,
      1,1,t,
    };
    RTSNavigationLib::MapChunk chunk(obstacles, resolution, true);
    RTSNavigationLib::MapChunk chunkD(obstacles, resolution, false);
    float costUp = chunk.getTraverseCost(RTSNavigationLib::MajorDirection2D::Top, 0, RTSNavigationLib::MajorDirection2D::Right, 0);
    float costDown = chunk.getTraverseCost(RTSNavigationLib::MajorDirection2D::Right, 0, RTSNavigationLib::MajorDirection2D::Top, 0);
    float costUpD = chunkD.getTraverseCost(RTSNavigationLib::MajorDirection2D::Top, 0, RTSNavigationLib::MajorDirection2D::Right, 0);
    float costDownD = chunkD.getTraverseCost(RTSNavigationLib::MajorDirection2D::Right, 0, RTSNavigationLib::MajorDirection2D::Top, 0);

    REQUIRE(chunk.numberPortals(RTSNavigationLib::MajorDirection2D::Left) == 1);
    REQUIRE(chunk.numberPortals(RTSNavigationLib::MajorDirection2D::Right) == 1);
    REQUIRE(chunk.numberPortals(RTSNavigationLib::MajorDirection2D::Bot) == 1);
    REQUIRE(chunk.numberPortals(RTSNavigationLib::MajorDirection2D::Top) == 1);

    REQUIRE(costUp    == 3);
    REQUIRE(costDown  == 3);
    REQUIRE(costUpD   == 3);
    REQUIRE(costDownD == 3);
  }
}