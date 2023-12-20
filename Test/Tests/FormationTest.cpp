#include <catch2/catch_test_macros.hpp>

#include <glm/gtc/matrix_transform.hpp>

#include <RTSPathingLib/Body.h>
#include "RTSPathingLib/Formation/FormationCalculator.h"
#include "RTSPathingLib/Formation/Formation.h"

TEST_CASE("Formation/single", "[FormationSingle]") {
  RTSPathingLib::Body b;
  b.category = 0;
  b.size = 1;
  b.position = glm::vec2(99, 99);

  std::vector<RTSPathingLib::Body> input = { b };
  RTSPathingLib::Formation formation(nullptr);
  auto places = RTSPathingLib::FormationCalculator::calculate(formation, input);

  REQUIRE(input.size()      == input.size());  
  REQUIRE(input[0].category == b.category);
  REQUIRE(input[0].size     == b.size);
  REQUIRE(input[0].position.x == 0);
  REQUIRE(input[0].position.y == 0);
}
