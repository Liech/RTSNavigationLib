#include <catch2/catch_test_macros.hpp>

#include <set>

#include <RTSPathingLib/Body.h>
#include <RTSPathingLib/Usher/Usher.h>
#include <RTSPathingLib/Usher/BoostMinCostFlowExample.h>
#include <RTSPathingLib/Formation/Formation.h>
#include <RTSPathingLib/Formation/FormationCalculator.h>

namespace UsherTests {
  bool svgSave = false;

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

  TEST_CASE("Usher/RectangleFormation", "[UsherFour]") {

    std::string formationDescription = R"""(
      {
        "OwnInterfacePoint"                : 0,  
        "ParentInterfacePoint"             : 0, 
        "OverwriteWidthWithInterfaceWidth" : false, 
        "RotateWithInterface"              : false, 
        "Rotation"                         : 0, 
        "UnitCategory"                     : 0, 
        "UnitDistributionWeight"           : 1,
        "Children"                         : {},

        "Shape" : {
          "Type" : "Rectangle",
          "Size" : [1,1],
          "Scaling" : "Isotropic"
        }
      }
    )""";
    auto formation = RTSPathingLib::Formation();
    formation.fromJson(nlohmann::json::parse(formationDescription));

    std::vector<RTSPathingLib::Body> units;

    units.push_back(RTSPathingLib::Body(glm::dvec2(4, 6), 0, 1));
    units.push_back(RTSPathingLib::Body(glm::dvec2(-3, 5), 0, 1));
    units.push_back(RTSPathingLib::Body(glm::dvec2(3, 2), 0, 1));
    units.push_back(RTSPathingLib::Body(glm::dvec2(5, 3), 0, 1));
    units.push_back(RTSPathingLib::Body(glm::dvec2(3, 5), 0, 1));
    units.push_back(RTSPathingLib::Body(glm::dvec2(2, 3), 0, 1));
    units.push_back(RTSPathingLib::Body(glm::dvec2(0, 1), 0, 1));

    units.push_back(RTSPathingLib::Body(glm::dvec2(-3, -2), 0, 1));
    units.push_back(RTSPathingLib::Body(glm::dvec2(-2, 4), 0, 1));
    units.push_back(RTSPathingLib::Body(glm::dvec2(2, -5), 0, 1));
    units.push_back(RTSPathingLib::Body(glm::dvec2(-3, -5), 0, 1));

    auto places = RTSPathingLib::FormationCalculator(formation, units).calculate();

    std::vector<size_t> tickets = RTSPathingLib::Usher::assignPlaces(units, places);

    if (svgSave)
      RTSPathingLib::Usher::visualize(tickets, units, places);

    std::set<size_t> x(tickets.begin(), tickets.end());
    REQUIRE(x.size() == tickets.size());

    REQUIRE(tickets[0 ] == 5 );
    REQUIRE(tickets[1 ] == 10);
    REQUIRE(tickets[2 ] == 9);
    REQUIRE(tickets[3 ] == 7);
    REQUIRE(tickets[4 ] == 4);
    REQUIRE(tickets[5 ] == 1);
    REQUIRE(tickets[6 ] == 0);
    REQUIRE(tickets[7 ] == 2);
    REQUIRE(tickets[8 ] == 6);
    REQUIRE(tickets[9 ] == 3);
    REQUIRE(tickets[10] == 8);
  }

  TEST_CASE("Usher/BoostMinCostFlowExample", "[UsherFour]") {
    RTSPathingLib::BoostMinCostFlowExample playground;
  }
}