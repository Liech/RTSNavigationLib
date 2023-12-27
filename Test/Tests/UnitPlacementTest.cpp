#include <catch2/catch_test_macros.hpp>

#include <RTSPathingLib/Body.h>

#include <RTSPathingLib/Formation/UnitPlacement.h>

namespace BodyUtilTests {
  TEST_CASE("UnitPlacement/OneSize1", "[UnitPlacement]") {
    RTSPathingLib::RectangleGrid<bool> grid;
    grid.dimension = glm::ivec2(1, 1);
    grid.data = { true };
    grid.offset = glm::dvec2(82, 82);
    std::map<size_t, size_t> unitsToPlace;
    size_t size = 1;
    unitsToPlace[size] = 1;
    size_t category = 123;
    RTSPathingLib::UnitPlacement placement(grid, unitsToPlace, 123);

    bool success = false;
    std::vector<RTSPathingLib::Body> result = placement.place(success);
    REQUIRE(success);
    REQUIRE(result.size() == 1);
    REQUIRE(result[0].category == category);
  }

  TEST_CASE("UnitPlacement/FailedPlacement", "[UnitPlacement]") {
    RTSPathingLib::RectangleGrid<bool> grid;
    grid.dimension = glm::ivec2(1, 1);
    grid.data = { false };
    grid.offset = glm::dvec2(82, 82);
    std::map<size_t, size_t> unitsToPlace;
    size_t size = 1;
    unitsToPlace[size] = 1;
    size_t category = 123;
    RTSPathingLib::UnitPlacement placement(grid, unitsToPlace, 123);

    bool success = false;
    std::vector<RTSPathingLib::Body> result = placement.place(success);
    REQUIRE(!success);
    REQUIRE(result.size() == 0);
  }

  TEST_CASE("UnitPlacement/OneSize2", "[UnitPlacement]") {
    RTSPathingLib::RectangleGrid<bool> grid;
    grid.dimension = glm::ivec2(2, 2);
    grid.data = { true , true ,
                  true , true };
    grid.offset = glm::dvec2(82, 82);
    std::map<size_t, size_t> unitsToPlace;
    size_t size = 2;
    unitsToPlace[size] = 1;
    size_t category = 123;
    RTSPathingLib::UnitPlacement placement(grid, unitsToPlace, 123);

    bool success = false;
    std::vector<RTSPathingLib::Body> result = placement.place(success);
    REQUIRE(success);
    REQUIRE(result.size() == 1);
    REQUIRE(result[0].category == category);
  }

  TEST_CASE("UnitPlacement/OneSize3", "[UnitPlacement]") {
    RTSPathingLib::RectangleGrid<bool> grid;
    grid.dimension = glm::ivec2(3, 3);
    grid.data = { true, true, true,
                  true, true, true,
                  true, true, true };
    grid.offset = glm::dvec2(82, 82);
    std::map<size_t, size_t> unitsToPlace;
    size_t size = 3;
    unitsToPlace[size] = 1;
    size_t category = 123;
    RTSPathingLib::UnitPlacement placement(grid, unitsToPlace, 123);

    bool success = false;
    std::vector<RTSPathingLib::Body> result = placement.place(success);
    REQUIRE(success);
    REQUIRE(result.size() == 1);
    REQUIRE(result[0].category == category);
  }

  TEST_CASE("UnitPlacement/FailedPlacementSize3", "[UnitPlacement]") {
    RTSPathingLib::RectangleGrid<bool> grid;
    grid.dimension = glm::ivec2(2, 2);
    grid.data = { true, true,
                  true, true};
    grid.offset = glm::dvec2(82, 82);
    std::map<size_t, size_t> unitsToPlace;
    size_t size = 3;
    unitsToPlace[size] = 1;
    size_t category = 123;
    RTSPathingLib::UnitPlacement placement(grid, unitsToPlace, 123);

    bool success = false;
    std::vector<RTSPathingLib::Body> result = placement.place(success);
    REQUIRE(!success);
    REQUIRE(result.size() == 0);
  }


  TEST_CASE("UnitPlacement/TwoSizeTwo", "[UnitPlacement]") {
    RTSPathingLib::RectangleGrid<bool> grid;
    grid.dimension = glm::ivec2(4, 2);
    grid.data = { true , true , true , true ,
                  true , true , true , true , };
    grid.offset = glm::dvec2(82, 82);
    std::map<size_t, size_t> unitsToPlace;
    size_t size = 2;
    unitsToPlace[size] = 2;
    size_t category = 123;
    RTSPathingLib::UnitPlacement placement(grid, unitsToPlace, 123);

    bool success = false;
    std::vector<RTSPathingLib::Body> result = placement.place(success);
    REQUIRE(success);
    REQUIRE(result.size() == 2);
    REQUIRE(result[0].category == category);
    REQUIRE(result[0].position.x == result[1].position.x - 2);
  }
}