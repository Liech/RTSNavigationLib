#include <catch2/catch_test_macros.hpp>

#include <RTSPathingLib/Body.h>

#include <RTSPathingLib/Formation/UnitPlacement.h>

namespace BodyUtilTests {
  TEST_CASE("UnitPlacement/Size1", "[UnitPlacement]") {
    RTSPathingLib::RectangleGrid<bool> grid;
    grid.dimension = glm::ivec2(1, 1);
    grid.data = { true };
    grid.offset = glm::dvec2(82, 82);
    std::map<size_t, size_t> unitsToPlace;
    unitsToPlace[1] = 1;
    size_t category = 123;
    RTSPathingLib::UnitPlacement placement(grid, unitsToPlace, 123);

    bool success = false;
    std::vector<RTSPathingLib::Body> result = placement.place(success);
    REQUIRE(success);
    REQUIRE(result.size() == 1);
    REQUIRE(result[0].category == category);
  }
}