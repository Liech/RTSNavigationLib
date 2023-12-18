#include <catch2/catch_test_macros.hpp>

#include <set>

#include <RTSPathingLib/Usher.h>
#include <RTSPathingLib/Body.h>

TEST_CASE("Usher/single", "[UsherSingle]") {
  std::vector<RTSPathingLib::Body> units  = { RTSPathingLib::Body(glm::vec2(0,0),0) };
  std::vector<RTSPathingLib::Body> places = { RTSPathingLib::Body(glm::vec2(0,0),0) };

  std::vector<size_t> tickets = RTSPathingLib::Usher::assignPlaces(units, places);

  REQUIRE(tickets.size() == units.size());
  REQUIRE(tickets[0] == 0);
}


TEST_CASE("Usher/swapped", "[UsherSwapped]") {
  std::vector<RTSPathingLib::Body> units = { RTSPathingLib::Body(glm::vec2(0,0),0),RTSPathingLib::Body(glm::vec2(1,0),0) };
  std::vector<RTSPathingLib::Body> places = { RTSPathingLib::Body(glm::vec2(1,0),0),RTSPathingLib::Body(glm::vec2(0,0),0) };

  std::vector<size_t> tickets = RTSPathingLib::Usher::assignPlaces(units, places);

  REQUIRE(tickets.size() == units.size());
  REQUIRE(tickets[0] == 1);
  REQUIRE(tickets[1] == 0);
}

TEST_CASE("Usher/Four", "[UsherFour]") {
  std::vector<RTSPathingLib::Body> units = { 
    RTSPathingLib::Body(glm::vec2( 1, 0),0),
    RTSPathingLib::Body(glm::vec2(-1, 0),0),
    RTSPathingLib::Body(glm::vec2( 0, 1),0),
    RTSPathingLib::Body(glm::vec2( 0,-1),0)
  };
  std::vector<RTSPathingLib::Body> places = {
    RTSPathingLib::Body(glm::vec2( 0, 132),0),
    RTSPathingLib::Body(glm::vec2( 4323, -12),0),
    RTSPathingLib::Body(glm::vec2( 33, 33),0),
    RTSPathingLib::Body(glm::vec2( -222222222, -455),0),
  };

  std::vector<size_t> tickets = RTSPathingLib::Usher::assignPlaces(units, places);

  std::set<size_t> x(tickets.begin(), tickets.end());
  REQUIRE(x.size() == tickets.size());

  REQUIRE(tickets.size() == units.size());
  REQUIRE(tickets[0] == 3);
  REQUIRE(tickets[1] == 2);
  REQUIRE(tickets[2] == 1);
  REQUIRE(tickets[3] == 0);
}