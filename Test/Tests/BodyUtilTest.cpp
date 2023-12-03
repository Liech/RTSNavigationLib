#include <catch2/catch_test_macros.hpp>

#include <glm/gtc/matrix_transform.hpp>

#include <RTSPathingLib/BodyUtil.h>
#include <RTSPathingLib/Body.h>

TEST_CASE("BodyUtil/identitySingle", "[BodyUtilidentitySingle]") {
  RTSPathingLib::Body b;
  b.position = glm::vec2(2, 3);
  b.blueprintID = 3;
  glm::mat4 identity = glm::mat4(1);

  RTSPathingLib::Body result = RTSPathingLib::BodyUtil::transform(b, identity);

  REQUIRE(result.blueprintID == b.blueprintID);
  REQUIRE(result.position[0] == 2);
  REQUIRE(result.position[1] == 3);
}

TEST_CASE("BodyUtil/single", "[BodyUtilSingle]") {
  RTSPathingLib::Body b;
  b.position = glm::vec2(2, 3);
  b.blueprintID = 5;
  glm::vec3 move = glm::vec3(3, 4, 0);
  glm::mat4 transform = glm::translate(glm::mat4(1), move);

  RTSPathingLib::Body result = RTSPathingLib::BodyUtil::transform(b, transform);

  REQUIRE(result.blueprintID == b.blueprintID);
  REQUIRE(result.position[0] == 5);
  REQUIRE(result.position[1] == 7);
}

TEST_CASE("BodyUtil/multi", "[BodyUtilMulti]") {
  std::vector< RTSPathingLib::Body> input;  

  RTSPathingLib::Body a;
  a.position = glm::vec2(2, 3);
  a.blueprintID = 5;
  input.push_back(a);

  RTSPathingLib::Body b;
  b.position = glm::vec2(4, 5);
  b.blueprintID = 7;
  input.push_back(b);

  glm::vec3 move = glm::vec3(1, 2, 0);
  glm::mat4 transform = glm::translate(glm::mat4(1), move);

  std::vector<RTSPathingLib::Body> result = RTSPathingLib::BodyUtil::transform(input, transform);

  REQUIRE(result.size() == 2);
  REQUIRE(result[0].blueprintID == a.blueprintID);
  REQUIRE(result[1].blueprintID == b.blueprintID);
  REQUIRE(result[0].position[0] == 3);
  REQUIRE(result[0].position[1] == 5);
  REQUIRE(result[1].position[0] == 5);
  REQUIRE(result[1].position[1] == 7);
}