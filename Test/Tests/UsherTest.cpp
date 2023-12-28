#include <catch2/catch_test_macros.hpp>

#include <set>

#include <RTSPathingLib/Body.h>
#include <RTSPathingLib/Usher/Usher.h>
#include <RTSPathingLib/Usher/BoostMinCostFlowExample.h>

namespace UsherTests {
  bool svgSave = true;

  TEST_CASE("Usher/single", "[UsherSingle]") {
    std::vector<RTSPathingLib::Body> units = { RTSPathingLib::Body(glm::dvec2(0,0),0) };
    std::vector<RTSPathingLib::Body> places = { RTSPathingLib::Body(glm::dvec2(0,0),0) };

    std::vector<size_t> tickets = RTSPathingLib::Usher::assignPlaces(units, places);

    if (svgSave)
      RTSPathingLib::Usher::visualize(tickets, units, places);

    REQUIRE(tickets.size() == units.size());
    REQUIRE(tickets[0] == 0);

  }


  TEST_CASE("Usher/swapped", "[UsherSwapped]") {
    std::vector<RTSPathingLib::Body> units = { RTSPathingLib::Body(glm::dvec2(0,0),0),RTSPathingLib::Body(glm::dvec2(1,0),0) };
    std::vector<RTSPathingLib::Body> places = { RTSPathingLib::Body(glm::dvec2(1,0),0),RTSPathingLib::Body(glm::dvec2(0,0),0) };

    std::vector<size_t> tickets = RTSPathingLib::Usher::assignPlaces(units, places);

    if (svgSave)
      RTSPathingLib::Usher::visualize(tickets, units, places);

    REQUIRE(tickets.size() == units.size());
    REQUIRE(tickets[0] == 1);
    REQUIRE(tickets[1] == 0);
  }

  TEST_CASE("Usher/Four", "[UsherFour]") {
    std::vector<RTSPathingLib::Body> units = {
      RTSPathingLib::Body(glm::dvec2(0, 7),0),
      RTSPathingLib::Body(glm::dvec2(4, -5),0),
      RTSPathingLib::Body(glm::dvec2(8, 8),0),
      RTSPathingLib::Body(glm::dvec2(-4, -6),0),
    };
    std::vector<RTSPathingLib::Body> places = {
      RTSPathingLib::Body(glm::dvec2(1, 0),0),
      RTSPathingLib::Body(glm::dvec2(-1, 0),0),
      RTSPathingLib::Body(glm::dvec2(0, 1),0),
      RTSPathingLib::Body(glm::dvec2(0,-1),0)
    };

    std::vector<size_t> tickets = RTSPathingLib::Usher::assignPlaces(units, places);

    if (svgSave)
      RTSPathingLib::Usher::visualize(tickets, units, places);

    std::set<size_t> x(tickets.begin(), tickets.end());
    REQUIRE(x.size() == tickets.size());

    REQUIRE(tickets.size() == units.size());
    REQUIRE(tickets[0] == 2);
    REQUIRE(tickets[1] == 3);
    REQUIRE(tickets[2] == 0);
    REQUIRE(tickets[3] == 1);

  }

  TEST_CASE("Usher/BoostMinCostFlowExample", "[UsherFour]") {
    RTSPathingLib::BoostMinCostFlowExample playground;
  }
}