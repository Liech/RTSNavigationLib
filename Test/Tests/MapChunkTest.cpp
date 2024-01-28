#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "RTSNavigationLib/Pathfinding/FlowField.h"
#include "RTSNavigationLib/Pathfinding/MapChunk.h"
#include "RTSNavigationLib/Pathfinding/EikonalGrid.h"

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
}