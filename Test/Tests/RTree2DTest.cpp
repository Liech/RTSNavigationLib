#include <catch2/catch_test_macros.hpp>

#include <RTSNavigationLib/Util/RTree2D.h>

namespace RTree2DTests {
  TEST_CASE("Util/rtree2d") {
    std::vector<std::pair<glm::dvec2, size_t>> input;
    input.push_back(std::make_pair(glm::dvec2(0, 0), 0));
    input.push_back(std::make_pair(glm::dvec2(1, 0), 1));
    input.push_back(std::make_pair(glm::dvec2(0, 1), 2));

    RTSNavigationLib::RTree2D tree(input);
    auto result = tree.nearestNeighbour(glm::dvec2(1.1, 0));
    REQUIRE(result.size() == 1);
    REQUIRE(result[0] == 1);
  }

  TEST_CASE("Util/rtree2dremove") {
    std::vector<std::pair<glm::dvec2, size_t>> input;
    input.push_back(std::make_pair(glm::dvec2(0, 0), 0));
    input.push_back(std::make_pair(glm::dvec2(1, 0), 1));
    input.push_back(std::make_pair(glm::dvec2(2, 0), 2));

    RTSNavigationLib::RTree2D tree(input);
    tree.remove(1);
    auto result = tree.nearestNeighbour(glm::dvec2(1.1, 0));
    REQUIRE(result.size() == 1);
    REQUIRE(result[0] == 2);
  }
}