#include <catch2/catch_test_macros.hpp>

#include <set>

#include <RTSNavigationLib/Body.h>
#include <RTSNavigationLib/Formation/Formation.h>
#include <RTSNavigationLib/Formation/FormationCalculator.h>
#include <RTSNavigationLib/Usher/BoostMinCostFlowExample.h>
#include <RTSNavigationLib/Usher/Usher.h>

namespace UsherTests
{
    bool svgSave = false;

    TEST_CASE("Usher/single")
    {
        std::vector<RTSNavigationLib::WorldBody> units  = { RTSNavigationLib::WorldBody(glm::dvec2(0, 0), 0) };
        std::vector<RTSNavigationLib::WorldBody> places = { RTSNavigationLib::WorldBody(glm::dvec2(0, 0), 0) };

        std::vector<size_t> tickets = RTSNavigationLib::Usher::assignPlaces(units, places);

        if (svgSave)
            RTSNavigationLib::Usher::visualize(tickets, units, places);

        REQUIRE(tickets.size() == units.size());
        REQUIRE(tickets[0] == 0);
    }

    TEST_CASE("Usher/swapped")
    {
        std::vector<RTSNavigationLib::WorldBody> units  = { RTSNavigationLib::WorldBody(glm::dvec2(0, 0), 0), RTSNavigationLib::WorldBody(glm::dvec2(1, 0), 0) };
        std::vector<RTSNavigationLib::WorldBody> places = { RTSNavigationLib::WorldBody(glm::dvec2(1, 0), 0), RTSNavigationLib::WorldBody(glm::dvec2(0, 0), 0) };

        std::vector<size_t> tickets = RTSNavigationLib::Usher::assignPlaces(units, places);

        if (svgSave)
            RTSNavigationLib::Usher::visualize(tickets, units, places);

        REQUIRE(tickets.size() == units.size());
        REQUIRE(tickets[0] == 1);
        REQUIRE(tickets[1] == 0);
    }

    TEST_CASE("Usher/Four")
    {
        std::vector<RTSNavigationLib::WorldBody> units = {
            RTSNavigationLib::WorldBody(glm::dvec2(0, 7), 0),
            RTSNavigationLib::WorldBody(glm::dvec2(4, -5), 0),
            RTSNavigationLib::WorldBody(glm::dvec2(8, 8), 0),
            RTSNavigationLib::WorldBody(glm::dvec2(-4, -6), 0),
        };
        std::vector<RTSNavigationLib::WorldBody> places = { RTSNavigationLib::WorldBody(glm::dvec2(1, 0), 0),
                                                            RTSNavigationLib::WorldBody(glm::dvec2(-1, 0), 0),
                                                            RTSNavigationLib::WorldBody(glm::dvec2(0, 1), 0),
                                                            RTSNavigationLib::WorldBody(glm::dvec2(0, -1), 0) };

        std::vector<size_t> tickets = RTSNavigationLib::Usher::assignPlaces(units, places);

        if (svgSave)
            RTSNavigationLib::Usher::visualize(tickets, units, places);

        std::set<size_t> x(tickets.begin(), tickets.end());
        REQUIRE(x.size() == tickets.size());

        REQUIRE(tickets.size() == units.size());

        bool optionA = true;
        bool optionB = true;

        optionA |= tickets[0] == 2;
        optionA |= tickets[1] == 3;
        optionA |= tickets[2] == 0;
        optionA |= tickets[3] == 1;

        optionB |= tickets[0] == 1;
        optionB |= tickets[1] == 0;
        optionB |= tickets[2] == 2;
        optionB |= tickets[3] == 3;

        bool valid = optionA || optionB;
        REQUIRE(valid);
    }

    TEST_CASE("Usher/RectangleFormation")
    {

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
        "PlacementBehavior"                : "CenterFirst",

        "Shape" : {
          "Type"    : "Rectangle",
          "Size"    : [1,1],
          "Scaling" : "Isotropic",
          "Hollow"  : 0
        }
      }
    )""";
        auto        formation            = RTSNavigationLib::Formation();
        formation.fromJson(nlohmann::json::parse(formationDescription));

        std::vector<RTSNavigationLib::WorldBody> units;

        units.push_back(RTSNavigationLib::WorldBody(glm::dvec2(4, 6), 0, 1));
        units.push_back(RTSNavigationLib::WorldBody(glm::dvec2(-3, 5), 0, 1));
        units.push_back(RTSNavigationLib::WorldBody(glm::dvec2(3, 2), 0, 1));
        units.push_back(RTSNavigationLib::WorldBody(glm::dvec2(5, 3), 0, 1));
        units.push_back(RTSNavigationLib::WorldBody(glm::dvec2(3, 5), 0, 1));
        units.push_back(RTSNavigationLib::WorldBody(glm::dvec2(2, 3), 0, 1));
        units.push_back(RTSNavigationLib::WorldBody(glm::dvec2(0, 1), 0, 1));

        units.push_back(RTSNavigationLib::WorldBody(glm::dvec2(-3, -2), 0, 1));
        units.push_back(RTSNavigationLib::WorldBody(glm::dvec2(-2, 4), 0, 1));
        units.push_back(RTSNavigationLib::WorldBody(glm::dvec2(2, -5), 0, 1));
        units.push_back(RTSNavigationLib::WorldBody(glm::dvec2(-3, -5), 0, 1));

        auto places = RTSNavigationLib::FormationCalculator(formation, units).calculate();

        std::vector<size_t> tickets = RTSNavigationLib::Usher::assignPlaces(units, places);

        if (svgSave)
            RTSNavigationLib::Usher::visualize(tickets, units, places);

        std::set<size_t> x(tickets.begin(), tickets.end());
        REQUIRE(x.size() == tickets.size());

        bool optionA = true;

        optionA |= tickets[0] == 5;
        optionA |= tickets[1] == 10;
        optionA |= tickets[2] == 9;
        optionA |= tickets[3] == 7;
        optionA |= tickets[4] == 4;
        optionA |= tickets[5] == 1;
        optionA |= tickets[6] == 0;
        optionA |= tickets[7] == 2;
        optionA |= tickets[8] == 6;
        optionA |= tickets[9] == 3;
        optionA |= tickets[10] == 8;

        bool optionB = true;

        optionB |= tickets[0] == 5;
        optionB |= tickets[1] == 6;
        optionB |= tickets[2] == 9;
        optionB |= tickets[3] == 7;
        optionB |= tickets[4] == 4;
        optionB |= tickets[5] == 1;
        optionB |= tickets[6] == 0;
        optionB |= tickets[7] == 2;
        optionB |= tickets[8] == 10;
        optionB |= tickets[9] == 3;
        optionB |= tickets[10] == 8;

        bool option = optionA || optionB;

        REQUIRE(option);
    }

    TEST_CASE("Usher/BoostMinCostFlowExample")
    {
        RTSNavigationLib::BoostMinCostFlowExample playground;
    }

    TEST_CASE("Usher/performance")
    {
        std::vector<RTSNavigationLib::WorldBody> units;
        std::vector<RTSNavigationLib::WorldBody> places;

        auto   randf  = []() { return (rand() % 1000) / 50.0 - 10.0; };
        size_t amount = 1000;
        for (size_t i = 0; i < amount; i++)
        {
            units.push_back(RTSNavigationLib::WorldBody(glm::dvec2(randf(), randf()), 0));
            places.push_back(RTSNavigationLib::WorldBody(glm::dvec2(randf(), randf()), 0));
        }

        std::vector<size_t> tickets = RTSNavigationLib::Usher::assignPlaces(units, places);

        if (svgSave)
            RTSNavigationLib::Usher::visualize(tickets, units, places);

        REQUIRE(tickets.size() == units.size());
    }

}