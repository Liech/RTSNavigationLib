#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>


#include "RTSNavigationLib/Pathfinding/MapChunk.h"
#include "RTSNavigationLib/Pathfinding/Map.h"
#include "RTSNavigationLib/Pathfinding/FlowField.h"
#include "RTSNavigationLib/Pathfinding/EikonalGrid.h"
#include "RTSNavigationLib/Pathfinding/DijkstraGrid.h"

namespace FlockTest {
  TEST_CASE("Map/InputCheck") {
    glm::ivec2 resolution    = glm::ivec2(4, 4);
    glm::ivec2 subResolution = glm::ivec2(2, 2);
    std::vector<float> obstacles = {
      1,1,1,1,
      1,1,1,1,
      1,1,1,1,
      1,1,1,1,
    };
    RTSNavigationLib::Map map(obstacles, resolution,subResolution,1, true);
    REQUIRE(map.getResolution() == glm::ivec2(4, 4));
    REQUIRE(map.getSubResolution() == glm::ivec2(2, 2));
    REQUIRE(map.getOverlap() == 1);
    REQUIRE(map.getEikonal() == true);
  }

  TEST_CASE("Map/SameMapChunk") {
    glm::ivec2 resolution = glm::ivec2(4, 4);
    glm::ivec2 subResolution = glm::ivec2(2, 2);
    glm::ivec2 start = glm::ivec2(0, 0);
    glm::ivec2 end = glm::ivec2(1, 0);
    std::vector<float> obstacles = {
      1,1,1,1,
      1,1,1,1,
      1,1,1,1,
      1,1,1,1,
    };
    RTSNavigationLib::Map map(obstacles, resolution, subResolution, 1, true);
    size_t mapID = map.getMap(start,end);
    const auto& flowField = map.getMap(mapID);
    glm::ivec2 offset = map.getOffset(mapID);

    auto dir = flowField.getDirection(offset + start);
    REQUIRE(dir[0] == 1);
    REQUIRE(dir[1] == 0);
    REQUIRE(map.hasMap(mapID));
  }
}