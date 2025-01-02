#include <catch2/catch_test_macros.hpp>

#include <RTSNavigationLib/Body.h>
#include <RTSNavigationLib/WorldBody.h>

#include <RTSNavigationLib/Formation/UnitPlacement.h>

namespace BodyUtilTests
{
    TEST_CASE("UnitPlacement/OneSize1")
    {
        RTSNavigationLib::RectangleGrid<bool> grid;
        grid.dimension = glm::ivec2(1, 1);
        grid.data      = { true };
        grid.offset    = glm::dvec2(82, 82);
        std::map<RTSNavigationLib::Body, size_t> unitsToPlace;

        RTSNavigationLib::Body b;
        b.category = 123;
        b.size     = 1;

        unitsToPlace[b] = 1;

        RTSNavigationLib::UnitPlacement placement(grid, unitsToPlace);

        bool                                     success = false;
        std::vector<RTSNavigationLib::WorldBody> result  = placement.place(success);
        REQUIRE(success);
        REQUIRE(result.size() == 1);
        REQUIRE(result[0].category == b.category);
    }

    TEST_CASE("UnitPlacement/FailedPlacement")
    {
        RTSNavigationLib::RectangleGrid<bool> grid;
        grid.dimension = glm::ivec2(1, 1);
        grid.data      = { false };
        grid.offset    = glm::dvec2(82, 82);
        std::map<RTSNavigationLib::Body, size_t> unitsToPlace;
        RTSNavigationLib::Body                   b;
        b.category      = 123;
        b.size          = 1;
        unitsToPlace[b] = 1;

        RTSNavigationLib::UnitPlacement placement(grid, unitsToPlace);

        bool                                     success = false;
        std::vector<RTSNavigationLib::WorldBody> result  = placement.place(success);
        REQUIRE(!success);
        REQUIRE(result.size() == 0);
    }

    TEST_CASE("UnitPlacement/OneSize2")
    {
        RTSNavigationLib::RectangleGrid<bool> grid;
        grid.dimension = glm::ivec2(2, 2);
        grid.data      = { true, true, true, true };
        grid.offset    = glm::dvec2(82, 82);
        std::map<RTSNavigationLib::Body, size_t> unitsToPlace;

        RTSNavigationLib::Body b;
        b.category      = 123;
        b.size          = 2;
        unitsToPlace[b] = 1;
        RTSNavigationLib::UnitPlacement placement(grid, unitsToPlace);

        bool                                     success = false;
        std::vector<RTSNavigationLib::WorldBody> result  = placement.place(success);
        REQUIRE(success);
        REQUIRE(result.size() == 1);
        REQUIRE(result[0].category == b.category);
    }

    TEST_CASE("UnitPlacement/OneSize3")
    {
        RTSNavigationLib::RectangleGrid<bool> grid;
        grid.dimension = glm::ivec2(3, 3);
        grid.data      = { true, true, true, true, true, true, true, true, true };
        grid.offset    = glm::dvec2(82, 82);
        std::map<RTSNavigationLib::Body, size_t> unitsToPlace;

        RTSNavigationLib::Body b;
        b.category      = 123;
        b.size          = 3;
        unitsToPlace[b] = 1;

        RTSNavigationLib::UnitPlacement placement(grid, unitsToPlace);

        bool                                     success = false;
        std::vector<RTSNavigationLib::WorldBody> result  = placement.place(success);
        REQUIRE(success);
        REQUIRE(result.size() == 1);
        REQUIRE(result[0].category == b.category);
    }

    TEST_CASE("UnitPlacement/FailedPlacementSize3")
    {
        RTSNavigationLib::RectangleGrid<bool> grid;
        grid.dimension = glm::ivec2(2, 2);
        grid.data      = { true, true, true, true };
        grid.offset    = glm::dvec2(82, 82);
        std::map<RTSNavigationLib::Body, size_t> unitsToPlace;

        RTSNavigationLib::Body b;
        b.category      = 123;
        b.size          = 3;
        unitsToPlace[b] = 1;

        RTSNavigationLib::UnitPlacement placement(grid, unitsToPlace);

        bool                                     success = false;
        std::vector<RTSNavigationLib::WorldBody> result  = placement.place(success);
        REQUIRE(!success);
        REQUIRE(result.size() == 0);
    }

    TEST_CASE("UnitPlacement/TwoSizeTwo")
    {
        RTSNavigationLib::RectangleGrid<bool> grid;
        grid.dimension = glm::ivec2(4, 2);
        grid.data      = {
            true, true, true, true, true, true, true, true,
        };
        grid.offset = glm::dvec2(82, 82);
        std::map<RTSNavigationLib::Body, size_t> unitsToPlace;

        RTSNavigationLib::Body b;
        b.category      = 123;
        b.size          = 2;
        unitsToPlace[b] = 2;

        RTSNavigationLib::UnitPlacement placement(grid, unitsToPlace);

        bool                                     success = false;
        std::vector<RTSNavigationLib::WorldBody> result  = placement.place(success);
        REQUIRE(success);
        REQUIRE(result.size() == 2);
        REQUIRE(result[0].category == b.category);
        REQUIRE((result[0].position.x == result[1].position.x - 2 || result[1].position.x == result[0].position.x - 2));
    }

    TEST_CASE("UnitPlacement/Mixed")
    {
        RTSNavigationLib::RectangleGrid<bool> grid;
        grid.dimension = glm::ivec2(4, 2);
        grid.data      = {
            true, true, true, true, true, true, true, true,
        };
        grid.offset = glm::dvec2(82, 82);
        std::map<RTSNavigationLib::Body, size_t> unitsToPlace;

        RTSNavigationLib::Body a;
        a.category = 123;
        a.size     = 1;
        RTSNavigationLib::Body b;
        b.category      = 123;
        b.size          = 2;
        unitsToPlace[a] = 4;
        unitsToPlace[b] = 1;
        RTSNavigationLib::UnitPlacement placement(grid, unitsToPlace);

        bool                                     success = false;
        std::vector<RTSNavigationLib::WorldBody> result  = placement.place(success);
        REQUIRE(success);
        REQUIRE(result.size() == 5);
        REQUIRE(result[0].size == 2);
        REQUIRE(result[1].size == 1);
        REQUIRE(result[2].size == 1);
        REQUIRE(result[3].size == 1);
        REQUIRE(result[4].size == 1);
        REQUIRE(glm::distance(result[0].position, result[1].position) >= 1.5);
        REQUIRE(glm::distance(result[0].position, result[2].position) >= 1.5);
        REQUIRE(glm::distance(result[0].position, result[3].position) >= 1.5);
        REQUIRE(glm::distance(result[0].position, result[4].position) >= 1.5);
    }

    TEST_CASE("UnitPlacement/ThreeSizes")
    {
        RTSNavigationLib::RectangleGrid<bool> grid;
        grid.dimension = glm::ivec2(6, 3);
        grid.data      = {
            true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true,
        };
        grid.offset = glm::dvec2(82, 82);
        std::map<RTSNavigationLib::Body, size_t> unitsToPlace;

        RTSNavigationLib::Body a;
        a.category = 123;
        a.size     = 1;

        RTSNavigationLib::Body b;
        b.category = 123;
        b.size     = 2;

        RTSNavigationLib::Body c;
        c.category = 123;
        c.size     = 3;

        unitsToPlace[a] = 5;
        unitsToPlace[b] = 1;
        unitsToPlace[c] = 1;

        RTSNavigationLib::UnitPlacement placement(grid, unitsToPlace);

        bool                                     success = false;
        std::vector<RTSNavigationLib::WorldBody> result  = placement.place(success);
        REQUIRE(success);
        REQUIRE(result.size() == 7);
        REQUIRE(result[0].size == 3);
        REQUIRE(result[1].size == 2);
        REQUIRE(result[2].size == 1);
        REQUIRE(result[3].size == 1);
        REQUIRE(result[4].size == 1);
        REQUIRE(result[5].size == 1);
        REQUIRE(result[6].size == 1);

        // size3
        REQUIRE(glm::distance(result[0].position, result[1].position) >= 2);
        REQUIRE(glm::distance(result[0].position, result[2].position) >= 2);
        REQUIRE(glm::distance(result[0].position, result[3].position) >= 2);
        REQUIRE(glm::distance(result[0].position, result[4].position) >= 2);
        REQUIRE(glm::distance(result[0].position, result[5].position) >= 2);
        REQUIRE(glm::distance(result[0].position, result[6].position) >= 2);

        // size2
        REQUIRE(glm::distance(result[1].position, result[2].position) >= 1.5);
        REQUIRE(glm::distance(result[1].position, result[3].position) >= 1.5);
        REQUIRE(glm::distance(result[1].position, result[4].position) >= 1.5);
        REQUIRE(glm::distance(result[1].position, result[5].position) >= 1.5);
        REQUIRE(glm::distance(result[1].position, result[6].position) >= 1.5);
    }
}