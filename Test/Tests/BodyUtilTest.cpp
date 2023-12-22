#include <catch2/catch_test_macros.hpp>

#include <glm/gtc/matrix_transform.hpp>

#include <RTSPathingLib/BodyUtil.h>
#include <RTSPathingLib/Body.h>

TEST_CASE("BodyUtil/identitySingle", "[BodyUtilidentitySingle]") {
  RTSPathingLib::Body b;
  b.position = glm::dvec2(2, 3);
  b.category = 3;
  b.size = 5;
  glm::dmat4 identity = glm::dmat4(1);

  RTSPathingLib::Body result = RTSPathingLib::BodyUtil::transform(b, identity);

  REQUIRE(result.category == b.category);
  REQUIRE(result.size == b.size);
  REQUIRE(result.position[0] == 2);
  REQUIRE(result.position[1] == 3);
}

TEST_CASE("BodyUtil/single", "[BodyUtilSingle]") {
  RTSPathingLib::Body b;
  b.position = glm::dvec2(2, 3);
  b.category = 5;
  b.size = 2;
  glm::dvec3 move = glm::dvec3(3, 4, 0);
  glm::dmat4 transform = glm::translate(glm::dmat4(1), move);

  RTSPathingLib::Body result = RTSPathingLib::BodyUtil::transform(b, transform);

  REQUIRE(result.category == b.category);
  REQUIRE(result.size == b.size);
  REQUIRE(result.position[0] == 5);
  REQUIRE(result.position[1] == 7);
}

TEST_CASE("BodyUtil/multi", "[BodyUtilMulti]") {
  std::vector< RTSPathingLib::Body> input;  

  RTSPathingLib::Body a;
  a.position = glm::dvec2(2, 3);
  a.category = 5;
  input.push_back(a);

  RTSPathingLib::Body b;
  b.position = glm::dvec2(4, 5);
  b.category = 7;
  input.push_back(b);

  glm::dvec3 move = glm::dvec3(1, 2, 0);
  glm::dmat4 transform = glm::translate(glm::dmat4(1), move);

  std::vector<RTSPathingLib::Body> result = RTSPathingLib::BodyUtil::transform(input, transform);

  REQUIRE(result.size() == 2);
  REQUIRE(result[0].category == a.category);
  REQUIRE(result[1].category == b.category);
  REQUIRE(result[0].position[0] == 3);
  REQUIRE(result[0].position[1] == 5);
  REQUIRE(result[1].position[0] == 5);
  REQUIRE(result[1].position[1] == 7);
}

TEST_CASE("BodyUtil/center", "[BodyUtilCenter]") {
  std::vector<RTSPathingLib::Body> input = { 
    RTSPathingLib::Body(glm::dvec2(5+-1,7 + 0),0),
    RTSPathingLib::Body(glm::dvec2(5+1 ,7 + 0) ,0),
    RTSPathingLib::Body(glm::dvec2(5+0 ,7 + 1) ,0),
    RTSPathingLib::Body(glm::dvec2(5+0 ,7 + -1),0)
  };

  glm::dvec2 result = RTSPathingLib::BodyUtil::getCenter(input);

  REQUIRE(result[0] == 5);
  REQUIRE(result[1] == 7);
}