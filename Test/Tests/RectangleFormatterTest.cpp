#include <catch2/catch_test_macros.hpp>

#include <RTSPathingLib/RectangleFormatter.h>
#include <RTSPathingLib/Body.h>


TEST_CASE("BasicRectangleFormatter/OneUnit", "[BRFOneUnit]") {
  RTSPathingLib::RectangleFormatter formatter;
  std::vector<size_t> units = { 0 };
  std::vector<double> radii = { 1 };

  std::vector<RTSPathingLib::Body> result = formatter.createRectGridFormation(glm::ivec2(1, 1), units, radii);

  REQUIRE(result.size() == 1);
  REQUIRE(result[0].blueprintID == 0);
  REQUIRE(result[0].position[0] == 0);
  REQUIRE(result[0].position[1] == 0);
}

TEST_CASE("BasicRectangleFormatter/ID", "[BRFID]") {
  RTSPathingLib::RectangleFormatter formatter;
  std::vector<size_t> units = { 5, 2 };
  std::vector<double> radii = { 0,0,0,0,0,0,0 };

  std::vector<RTSPathingLib::Body> result = formatter.createRectGridFormation(glm::ivec2(1,1), units, radii);

  REQUIRE(result.size() == 2);
  REQUIRE(result[0].blueprintID == 5);
  REQUIRE(result[1].blueprintID == 2);
}

TEST_CASE("BasicRectangleFormatter/TwoUnit", "[BRFOneUnit]") {
  RTSPathingLib::RectangleFormatter formatter;
  std::vector<size_t> units = { 0, 0 };
  std::vector<double> radii = { 1 };

  std::vector<RTSPathingLib::Body> result = formatter.createRectGridFormation(glm::ivec2(2, 1), units, radii);
  std::vector<RTSPathingLib::Body> result2 = formatter.createRectGridFormation(glm::ivec2(1, 2), units, radii);

  REQUIRE(result.size() == 2);
  REQUIRE(result2.size() == 2);
  REQUIRE(result[0].blueprintID == 0);
  REQUIRE(result[1].blueprintID == 0);
  REQUIRE(result2[0].blueprintID == 0);
  REQUIRE(result2[1].blueprintID == 0);

  REQUIRE(result[0].position[0] == 0);
  REQUIRE(result[0].position[1] == 0);
  REQUIRE(result[1].position[0] == 1);
  REQUIRE(result[1].position[1] == 0);

  REQUIRE(result2[0].position[0] == 0);
  REQUIRE(result2[0].position[1] == 0);
  REQUIRE(result2[1].position[0] == 0);
  REQUIRE(result2[1].position[1] == 1);
}

TEST_CASE("BasicRectangleFormatter/ThreeUnit", "[BRF3Unit]") {
  RTSPathingLib::RectangleFormatter formatter;
  std::vector<size_t> units = { 0, 1, 2};
  std::vector<double> radii = { 1,2,3 };

  std::vector<RTSPathingLib::Body> result = formatter.createRectGridFormation(glm::ivec2(2, 2), units, radii);

  REQUIRE(result.size() == 3);
  REQUIRE(result[0].blueprintID == 0);
  REQUIRE(result[1].blueprintID == 1);
  REQUIRE(result[2].blueprintID == 2);


  REQUIRE(result[0].position[0] == 0);
  REQUIRE(result[0].position[1] == 0);
  REQUIRE(result[1].position[0] == 3);
  REQUIRE(result[1].position[1] == 0);
  REQUIRE(result[2].position[0] == 0);
  REQUIRE(result[2].position[1] == 3);

}