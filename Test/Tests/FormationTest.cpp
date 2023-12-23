#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <glm/gtc/matrix_transform.hpp>

#include <RTSPathingLib/Body.h>
#include "RTSPathingLib/Formation/FormationCalculator.h"
#include "RTSPathingLib/Formation/Formation.h"
#include "RTSPathingLib/Formation/FormationShape/RectangleFormationShape.h"
#include "RTSPathingLib/Formation/FormationShape/ArcFormationShape.h"
#include "RTSPathingLib/Formation/FormationShape/TriangleFormationShape.h"

TEST_CASE("Formation/RectangleSingle", "[FormationSingle]") {
  RTSPathingLib::Body b;
  b.category = 0;
  b.size = 1;
  b.position = glm::dvec2(99, 99);

  std::vector<RTSPathingLib::Body> input = { b };
  RTSPathingLib::Formation formation;
  formation.setShape(std::make_unique<RTSPathingLib::RectangleFormationShape>());
  auto places = RTSPathingLib::FormationCalculator::calculate(formation, input);

  REQUIRE(places.size() == input.size());
  REQUIRE(places[0].category == b.category);
  REQUIRE(places[0].size == b.size);
  REQUIRE(places[0].position.x != 99);
  REQUIRE(places[0].position.y != 99);
}

TEST_CASE("Formation/RectangleDouble", "[FormationDouble]") {
  RTSPathingLib::Body b;
  b.category = 0;
  b.size = 1;
  b.position = glm::dvec2(99, 99);

  std::vector<RTSPathingLib::Body> input = { b, b };
  RTSPathingLib::Formation formation;
  formation.setShape(std::make_unique<RTSPathingLib::RectangleFormationShape>());
  auto places = RTSPathingLib::FormationCalculator::calculate(formation, input);

  REQUIRE(places.size() == input.size());
  REQUIRE(places[0].category == b.category);
  REQUIRE(places[0].size == b.size);
  REQUIRE(places[1].category == b.category);
  REQUIRE(places[1].size == b.size);
  REQUIRE(places[1].position.x == places[0].position.x + 1);
  REQUIRE(places[1].position.y == places[0].position.y);
}

TEST_CASE("Formation/RectangleMany", "[FormationDouble]") {
  RTSPathingLib::Body b;
  b.category = 0;
  b.size = 1;
  b.position = glm::dvec2(99, 99);

  std::vector<RTSPathingLib::Body> input = { };
  for (int i = 0; i < 16; i++)
    input.push_back(b);
  RTSPathingLib::Formation formation;
  formation.setShape(std::make_unique<RTSPathingLib::RectangleFormationShape>());
  auto places = RTSPathingLib::FormationCalculator::calculate(formation, input);

  REQUIRE(places.size() == input.size());
}

TEST_CASE("Formation/ArcSingle", "[FormationSingle]") {
  RTSPathingLib::Body b;
  b.category = 0;
  b.size = 1;
  b.position = glm::dvec2(99, 99);

  std::vector<RTSPathingLib::Body> input = { b };
  RTSPathingLib::Formation formation;
  formation.setShape(std::make_unique<RTSPathingLib::ArcFormationShape>());
  auto places = RTSPathingLib::FormationCalculator::calculate(formation, input);

  REQUIRE(places.size() == input.size());
  REQUIRE(places[0].category == b.category);
  REQUIRE(places[0].size == b.size);
  REQUIRE(places[0].position.x != 99);
  REQUIRE(places[0].position.y != 99);
}

TEST_CASE("Formation/ArcDouble", "[FormationDouble]") {
  RTSPathingLib::Body b;
  b.category = 0;
  b.size = 1;
  b.position = glm::dvec2(99, 99);

  std::vector<RTSPathingLib::Body> input = { b, b };
  RTSPathingLib::Formation formation;
  formation.setShape(std::make_unique<RTSPathingLib::ArcFormationShape>());
  auto places = RTSPathingLib::FormationCalculator::calculate(formation, input);

  REQUIRE(places.size() == input.size());
  REQUIRE(places[0].category == b.category);
  REQUIRE(places[0].size == b.size);
  REQUIRE(places[1].category == b.category);
  REQUIRE(places[1].size == b.size);
  REQUIRE(places[1].position.x == places[0].position.x + 1);
  REQUIRE(places[1].position.y == places[0].position.y);
}

TEST_CASE("Formation/ArcMany", "[FormationDouble]") {
  RTSPathingLib::Body b;
  b.category = 0;
  b.size = 1;
  b.position = glm::dvec2(99, 99);

  std::vector<RTSPathingLib::Body> input = { };
  for (int i = 0; i < 16; i++)
    input.push_back(b);
  RTSPathingLib::Formation formation;
  formation.setShape(std::make_unique<RTSPathingLib::ArcFormationShape>());
  auto places = RTSPathingLib::FormationCalculator::calculate(formation, input);

  REQUIRE(places.size() == input.size());
}

TEST_CASE("Formation/PartialArc", "[FormationDouble]") {
  RTSPathingLib::Body b;
  b.category = 0;
  b.size = 1;
  b.position = glm::dvec2(99, 99);

  std::vector<RTSPathingLib::Body> input = { };
  for (int i = 0; i < 16; i++)
    input.push_back(b);
  RTSPathingLib::Formation formation;
  auto shape = std::make_unique<RTSPathingLib::ArcFormationShape>();
  shape->setArcAngle(glm::pi<double>() * 1);
  formation.setShape(std::move(shape));
  auto places = RTSPathingLib::FormationCalculator::calculate(formation, input);

  REQUIRE(places.size() == input.size());
}

TEST_CASE("Formation/TriangleSingle", "[FormationSingle]") {
  RTSPathingLib::Body b;
  b.category = 0;
  b.size = 1;
  b.position = glm::dvec2(99, 99);

  std::vector<RTSPathingLib::Body> input = { b };
  RTSPathingLib::Formation formation;
  formation.setShape(std::make_unique<RTSPathingLib::TriangleFormationShape>());
  auto places = RTSPathingLib::FormationCalculator::calculate(formation, input);

  REQUIRE(places.size() == input.size());
  REQUIRE(places[0].category == b.category);
  REQUIRE(places[0].size == b.size);
  REQUIRE(places[0].position.x != 99);
  REQUIRE(places[0].position.y != 99);
}

TEST_CASE("Formation/TriangleDouble", "[FormationDouble]") {
  RTSPathingLib::Body b;
  b.category = 0;
  b.size = 1;
  b.position = glm::dvec2(99, 99);

  std::vector<RTSPathingLib::Body> input = { b, b };
  RTSPathingLib::Formation formation;
  formation.setShape(std::make_unique<RTSPathingLib::TriangleFormationShape>());
  auto places = RTSPathingLib::FormationCalculator::calculate(formation, input);

  REQUIRE(places.size() == input.size());
  REQUIRE(places[0].category == b.category);
  REQUIRE(places[0].size == b.size);
  REQUIRE(places[1].category == b.category);
  REQUIRE(places[1].size == b.size);
  REQUIRE(places[1].position.x == places[0].position.x + 1);
  REQUIRE(places[1].position.y == places[0].position.y);
}

TEST_CASE("Formation/TriangleMany", "[FormationDouble]") {
  RTSPathingLib::Body b;
  b.category = 0;
  b.size = 1;
  b.position = glm::dvec2(99, 99);

  std::vector<RTSPathingLib::Body> input = { };
  for (int i = 0; i < 16; i++)
    input.push_back(b);
  RTSPathingLib::Formation formation;
  formation.setShape(std::make_unique<RTSPathingLib::TriangleFormationShape>());
  auto places = RTSPathingLib::FormationCalculator::calculate(formation, input);

  REQUIRE(places.size() == input.size());
}

TEST_CASE("Formation/InterfacePoint", "[FormationSingle]") {
  RTSPathingLib::Body b;
  b.category = 0;
  b.size = 1;
  b.position = glm::dvec2(99, 99);

  std::vector<RTSPathingLib::Body> input = { b };
  RTSPathingLib::Formation formation;
  formation.setOwnInterfacePoint(5);
  formation.setShape(std::make_unique<RTSPathingLib::RectangleFormationShape>());
  auto places = RTSPathingLib::FormationCalculator::calculate(formation, input);

  REQUIRE(places.size() == input.size());
  REQUIRE(places[0].category == b.category);
  REQUIRE(places[0].size == b.size);
  REQUIRE(places[0].position.x != 99);
  REQUIRE(places[0].position.y != 99);
}

TEST_CASE("Formation/Rotation", "[FormationSingle]") {
  RTSPathingLib::Body b;
  b.category = 0;
  b.size = 1;
  b.position = glm::dvec2(99, 99);

  std::vector<RTSPathingLib::Body> input = { b };
  RTSPathingLib::Formation formation;
  formation.setOwnInterfacePoint(5);
  formation.setRotation(glm::pi<double>());
  formation.setShape(std::make_unique<RTSPathingLib::RectangleFormationShape>());
  auto places = RTSPathingLib::FormationCalculator::calculate(formation, input);

  REQUIRE(places.size() == input.size());
  REQUIRE(places[0].category == b.category);
  REQUIRE(places[0].size == b.size);
  REQUIRE(places[0].position.x != 99);
  REQUIRE(places[0].position.y != 99);
}

TEST_CASE("Formation/OneChild", "[FormationSingle]") {
  RTSPathingLib::Body a;
  a.category = 0;
  a.size = 1;
  a.position = glm::dvec2(99, 99);
  RTSPathingLib::Body b;
  b.category = 1;
  b.size = 1;
  b.position = glm::dvec2(99, 99);

  std::vector<RTSPathingLib::Body> input = { a, a, b, b, b, b };
  RTSPathingLib::Formation formation;
  formation.setShape(std::make_unique<RTSPathingLib::RectangleFormationShape>());
  formation.setUnitCategory(0);

  std::unique_ptr<RTSPathingLib::Formation> formation2 = std::make_unique<RTSPathingLib::Formation>();
  formation2->setShape(std::make_unique<RTSPathingLib::RectangleFormationShape>());
  formation2->setUnitCategory(1);
  formation2->setParentInterfacePoint(9);
  formation2->setOwnInterfacePoint(5);
  formation.addChild(std::move(formation2));

  auto places = RTSPathingLib::FormationCalculator::calculate(formation, input);

  REQUIRE(places.size() == input.size());
  REQUIRE(places[0].category == a.category);
  REQUIRE(places[1].category == a.category);
  REQUIRE(places[2].category == b.category);
  REQUIRE(places[3].category == b.category);
  REQUIRE(places[4].category == b.category);
  REQUIRE(places[5].category == b.category);

  REQUIRE(places[1].position.x == places[0].position.x + 1);
  REQUIRE(places[1].position.y == places[0].position.y + 0);
  REQUIRE(places[2].position.x == places[0].position.x + 0);
  REQUIRE(places[2].position.y == places[0].position.y + 1);
  REQUIRE(places[3].position.x == places[0].position.x + 1);
  REQUIRE(places[3].position.y == places[0].position.y + 1);
  REQUIRE(places[4].position.x == places[0].position.x + 0);
  REQUIRE(places[4].position.y == places[0].position.y + 2);
  REQUIRE(places[5].position.x == places[0].position.x + 1);
  REQUIRE(places[5].position.y == places[0].position.y + 2);
}

TEST_CASE("Formation/OneChild2", "[FormationSingle]") {
  RTSPathingLib::Body a;
  a.category = 0;
  a.size = 1;
  a.position = glm::dvec2(99, 99);
  RTSPathingLib::Body b;
  b.category = 1;
  b.size = 1;
  b.position = glm::dvec2(99, 99);

  std::vector<RTSPathingLib::Body> input = { a, a, a, a, b, b, b, b };
  RTSPathingLib::Formation formation;
  formation.setShape(std::make_unique<RTSPathingLib::RectangleFormationShape>());
  formation.setUnitCategory(0);

  std::unique_ptr<RTSPathingLib::Formation> formation2 = std::make_unique<RTSPathingLib::Formation>();
  formation2->setShape(std::make_unique<RTSPathingLib::RectangleFormationShape>());
  formation2->setUnitCategory(1);
  formation2->setParentInterfacePoint(9);
  formation2->setOwnInterfacePoint(5);
  formation.addChild(std::move(formation2));

  auto places = RTSPathingLib::FormationCalculator::calculate(formation, input);

  REQUIRE(places.size() == input.size());
  REQUIRE_THAT(places[0].position.x + 0.5, Catch::Matchers::WithinAbs(0, 0.01));
  REQUIRE_THAT(places[0].position.y + 0.5, Catch::Matchers::WithinAbs(0, 0.01));
  REQUIRE_THAT(places[1].position.x - 0.5, Catch::Matchers::WithinAbs(0, 0.01));
  REQUIRE_THAT(places[1].position.y + 0.5, Catch::Matchers::WithinAbs(0, 0.01));
  REQUIRE(places[0].category == a.category);
  REQUIRE(places[1].category == a.category);
  REQUIRE(places[2].category == a.category);
  REQUIRE(places[3].category == a.category);

  REQUIRE_THAT(places[4].position.x + 0.5, Catch::Matchers::WithinAbs(0, 0.01));
  REQUIRE_THAT(places[4].position.y - 1.5, Catch::Matchers::WithinAbs(0, 0.01));
  REQUIRE_THAT(places[5].position.x - 0.5, Catch::Matchers::WithinAbs(0, 0.01));
  REQUIRE_THAT(places[5].position.y - 1.5, Catch::Matchers::WithinAbs(0, 0.01));
  REQUIRE(places[4].category == b.category);
  REQUIRE(places[5].category == b.category);
  REQUIRE(places[6].category == b.category);
  REQUIRE(places[7].category == b.category);
}


TEST_CASE("Formation/OverlappingChild", "[FormationSingle]") {
  RTSPathingLib::Body a;
  a.category = 0;
  a.size = 1;
  a.position = glm::dvec2(99, 99);
  RTSPathingLib::Body b;
  b.category = 1;
  b.size = 1;
  b.position = glm::dvec2(99, 99);

  std::vector<RTSPathingLib::Body> input = { a,a, a, b, b, b, b, b, b, b, b };
  RTSPathingLib::Formation formation;
  formation.setShape(std::make_unique<RTSPathingLib::RectangleFormationShape>());
  formation.setUnitCategory(0);

  std::unique_ptr<RTSPathingLib::Formation> formation2 = std::make_unique<RTSPathingLib::Formation>();
  formation2->setShape(std::make_unique<RTSPathingLib::RectangleFormationShape>());
  formation2->setUnitCategory(1);
  formation2->setParentInterfacePoint(9);
  formation2->setOwnInterfacePoint(9); 
  formation.addChild(std::move(formation2));

  auto places = RTSPathingLib::FormationCalculator::calculate(formation, input);

  REQUIRE(places.size() == input.size());
  REQUIRE(places[0].position.x == -0.5);
  REQUIRE(places[0].position.y == -0.5);
  REQUIRE(places[1].position.x ==  0.5);
  REQUIRE(places[1].position.y == -0.5);
  REQUIRE(places[2].position.x == -0.5);
  REQUIRE(places[2].position.y ==  0.5);
  REQUIRE(places[3].position.x == -1.5);
  REQUIRE(places[3].position.y == -1.5);
  REQUIRE(places[4].position.x == -0.5);
  REQUIRE(places[4].position.y == -1.5);
  REQUIRE(places[5].position.x ==  0.5);
  REQUIRE(places[5].position.y == -1.5);
  REQUIRE(places[6].position.x ==  1.5);
  REQUIRE(places[6].position.y == -1.5);
  REQUIRE(places[7].position.x == -1.5);
  REQUIRE(places[7].position.y == -0.5);
  REQUIRE(places[8].position.x ==  1.5);
  REQUIRE(places[8].position.y == -0.5);
  REQUIRE(places[9].position.x == -1.5);
  REQUIRE(places[9].position.y == 0.5);
  REQUIRE(places[10].position.x == 1.5);
  REQUIRE(places[10].position.y == 0.5);
}

TEST_CASE("Formation/RotateChild", "[FormationSingle]") {
  RTSPathingLib::Body a;
  a.category = 0;
  a.size = 1;
  a.position = glm::dvec2(99, 99);
  RTSPathingLib::Body b;
  b.category = 1;
  b.size = 1;
  b.position = glm::dvec2(99, 99);

  std::vector<RTSPathingLib::Body> input = { a,a, a, b, b, b,};
  RTSPathingLib::Formation formation;
  formation.setShape(std::make_unique<RTSPathingLib::RectangleFormationShape>());
  formation.setUnitCategory(0);

  std::unique_ptr<RTSPathingLib::Formation> formation2 = std::make_unique<RTSPathingLib::Formation>();
  formation2->setShape(std::make_unique<RTSPathingLib::RectangleFormationShape>());
  formation2->setUnitCategory(1);
  formation2->setParentInterfacePoint(9);
  formation2->setOwnInterfacePoint(5);
  formation2->setRotation(glm::pi<float>() * 0.5);
  formation.addChild(std::move(formation2));

  auto places = RTSPathingLib::FormationCalculator::calculate(formation, input);

  REQUIRE(places.size() == input.size());
  REQUIRE(places[1].position.x == places[0].position.x + 1);
  REQUIRE(places[1].position.y == places[0].position.y + 0);
  REQUIRE(places[2].position.x == places[0].position.x + 0);
  REQUIRE(places[2].position.y == places[0].position.y + 1);
  REQUIRE(places[3].position.x == places[0].position.x - 1);
  REQUIRE(places[3].position.y == places[0].position.y + 1);
  REQUIRE(places[4].position.x == places[0].position.x - 1);
  REQUIRE(places[4].position.y == places[0].position.y + 2);
  REQUIRE(places[5].position.x == places[0].position.x - 0);
  REQUIRE(places[5].position.y == places[0].position.y + 2);
}


TEST_CASE("Formation/PraiseTheSun", "[FormationSingle]") {
  RTSPathingLib::Body a;
  a.category = 0;
  a.size = 1;
  a.position = glm::dvec2(99, 99);
  RTSPathingLib::Body b;
  b.category = 1;
  b.size = 1;
  b.position = glm::dvec2(99, 99);
  RTSPathingLib::Body c;
  c.category = 2;
  c.size = 1;
  c.position = glm::dvec2(99, 99);

  std::vector<RTSPathingLib::Body> input;
  for (size_t i = 0; i < 30; i++)
    input.push_back(a);
  for (size_t i = 0; i < 66; i++)
    input.push_back(b);
  for (size_t i = 0; i < 5; i++)
    input.push_back(c);
  RTSPathingLib::Formation formation;
  formation.setShape(std::make_unique<RTSPathingLib::ArcFormationShape>());
  formation.setUnitCategory(0);

  std::unique_ptr<RTSPathingLib::Formation> spike = std::make_unique<RTSPathingLib::Formation>();
  spike->setShape(std::make_unique<RTSPathingLib::TriangleFormationShape>());
  spike->setUnitCategory(2);
  spike->setOwnInterfacePoint(0);
  spike->setParentInterfacePoint(5);

  std::unique_ptr<RTSPathingLib::Formation> formation2 = std::make_unique<RTSPathingLib::Formation>();
  formation2->addChild(std::move(spike));
  formation2->setShape(std::make_unique<RTSPathingLib::ArcFormationShape>());
  formation2->setUnitCategory(1);
  formation.addChild(std::move(formation2));

  auto places = RTSPathingLib::FormationCalculator::calculate(formation, input);

  REQUIRE(places.size() == input.size());
}