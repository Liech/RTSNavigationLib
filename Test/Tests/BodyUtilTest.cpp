#include <catch2/catch_test_macros.hpp>

#include <glm/gtc/matrix_transform.hpp>

#include <RTSNavigationLib/BodyUtil.h>
#include <RTSNavigationLib/Body.h>

namespace BodyUtilTests {
  TEST_CASE("BodyUtil/identitySingle", "[BodyUtilidentitySingle]") {
    RTSNavigationLib::Body b;
    b.position = glm::dvec2(2, 3);
    b.category = 3;
    b.size = 5;
    glm::dmat4 identity = glm::dmat4(1);

    RTSNavigationLib::Body result = RTSNavigationLib::BodyUtil::transform(b, identity);

    REQUIRE(result.category == b.category);
    REQUIRE(result.size == b.size);
    REQUIRE(result.position[0] == 2);
    REQUIRE(result.position[1] == 3);
  }

  TEST_CASE("BodyUtil/single", "[BodyUtilSingle]") {
    RTSNavigationLib::Body b;
    b.position = glm::dvec2(2, 3);
    b.category = 5;
    b.size = 2;
    glm::dvec3 move = glm::dvec3(3, 4, 0);
    glm::dmat4 transform = glm::translate(glm::dmat4(1), move);

    RTSNavigationLib::Body result = RTSNavigationLib::BodyUtil::transform(b, transform);

    REQUIRE(result.category == b.category);
    REQUIRE(result.size == b.size);
    REQUIRE(result.position[0] == 5);
    REQUIRE(result.position[1] == 7);
  }

  TEST_CASE("BodyUtil/multi", "[BodyUtilMulti]") {
    std::vector< RTSNavigationLib::Body> input;

    RTSNavigationLib::Body a;
    a.position = glm::dvec2(2, 3);
    a.category = 5;
    input.push_back(a);

    RTSNavigationLib::Body b;
    b.position = glm::dvec2(4, 5);
    b.category = 7;
    input.push_back(b);

    glm::dvec3 move = glm::dvec3(1, 2, 0);
    glm::dmat4 transform = glm::translate(glm::dmat4(1), move);

    std::vector<RTSNavigationLib::Body> result = RTSNavigationLib::BodyUtil::transform(input, transform);

    REQUIRE(result.size() == 2);
    REQUIRE(result[0].category == a.category);
    REQUIRE(result[1].category == b.category);
    REQUIRE(result[0].position[0] == 3);
    REQUIRE(result[0].position[1] == 5);
    REQUIRE(result[1].position[0] == 5);
    REQUIRE(result[1].position[1] == 7);
  }

  TEST_CASE("BodyUtil/center", "[BodyUtilCenter]") {
    std::vector<RTSNavigationLib::Body> input = {
      RTSNavigationLib::Body(glm::dvec2(5 + -1,7 + 0),0),
      RTSNavigationLib::Body(glm::dvec2(5 + 1 ,7 + 0) ,0),
      RTSNavigationLib::Body(glm::dvec2(5 + 0 ,7 + 1) ,0),
      RTSNavigationLib::Body(glm::dvec2(5 + 0 ,7 + -1),0)
    };

    glm::dvec2 result = RTSNavigationLib::BodyUtil::getCenter(input);

    REQUIRE(result[0] == 5);
    REQUIRE(result[1] == 7);
  }
}