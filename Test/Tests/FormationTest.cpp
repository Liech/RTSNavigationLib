#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <set>

#include <RTSPathingLib/Body.h>
#include "RTSPathingLib/Formation/FormationCalculator.h"
#include "RTSPathingLib/Formation/Formation.h"
#include "RTSPathingLib/Formation/FormationShape/RectangleFormationShape.h"
#include "RTSPathingLib/Formation/FormationShape/ArcFormationShape.h"
#include "RTSPathingLib/Formation/FormationShape/TriangleFormationShape.h"
#include "RTSPathingLib/Formation/FormationShape/RectangleInterfacePoint.h"
#include "RTSPathingLib/Formation/FormationShape/TriangleInterfacePoint.h"

namespace FormationTests {
  struct lex_compare {
    bool operator() (const glm::dvec2& lhs, const glm::dvec2& rhs) const {
      return (lhs.x < rhs.x) || (lhs.x == rhs.x && lhs.y < rhs.y);
    }
  };

  glm::dvec2 getFirstPlace(std::vector<RTSPathingLib::Body> places) {
    glm::dvec2 first = glm::dvec2(std::numeric_limits<double>().max(), std::numeric_limits<double>().max());
    for (auto& x : places)
      if (lex_compare()(x.position, first))
        first = x.position;
    return first;
  }
  std::set<glm::dvec2, lex_compare> setisfy(const std::vector<RTSPathingLib::Body>& places) {
    auto first = getFirstPlace(places);
    std::set<glm::dvec2, lex_compare> result;
    for (auto& x : places)
      result.insert(x.position - first);
    return result;
  }

  std::map<size_t, size_t> countCategories(const std::vector<RTSPathingLib::Body>& places) {
    std::map<size_t, size_t> result;
    for (auto& x : places) {
      if (result.count(x.category) == 0)
        result[x.category] = 0;
      result[x.category]++;
    }
    return result;
  }


  TEST_CASE("Formation/RectangleSingle", "[FormationSingle]") {
    RTSPathingLib::Body b;
    b.category = 0;
    b.size = 1;
    b.position = glm::dvec2(99, 99);

    std::vector<RTSPathingLib::Body> input = { b };
    RTSPathingLib::Formation formation;
    formation.setShape(std::make_unique<RTSPathingLib::RectangleFormationShape>());
    auto places = RTSPathingLib::FormationCalculator(formation, input).calculate();

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
    auto places = RTSPathingLib::FormationCalculator(formation, input).calculate();

    REQUIRE(places.size() == input.size());
    REQUIRE(places[0].category == b.category);
    REQUIRE(places[0].size == b.size);
    REQUIRE(places[1].category == b.category);
    REQUIRE(places[1].size == b.size);

    auto result = setisfy(places);
    REQUIRE(result.contains(glm::dvec2(1, 0)));
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
    auto places = RTSPathingLib::FormationCalculator(formation, input).calculate();

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
    auto places = RTSPathingLib::FormationCalculator(formation, input).calculate();

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
    auto places = RTSPathingLib::FormationCalculator(formation, input).calculate();

    REQUIRE(places.size() == input.size());
    REQUIRE(places[0].category == b.category);
    REQUIRE(places[0].size == b.size);
    REQUIRE(places[1].category == b.category);
    REQUIRE(places[1].size == b.size);

    auto result = setisfy(places);
    REQUIRE(result.contains(glm::dvec2(1, 0)));
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
    auto places = RTSPathingLib::FormationCalculator(formation, input).calculate();

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
    auto places = RTSPathingLib::FormationCalculator(formation, input).calculate();

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
    auto places = RTSPathingLib::FormationCalculator(formation, input).calculate();

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
    auto places = RTSPathingLib::FormationCalculator(formation, input).calculate();

    REQUIRE(places.size() == input.size());
    REQUIRE(places[0].category == b.category);
    REQUIRE(places[0].size == b.size);
    REQUIRE(places[1].category == b.category);
    REQUIRE(places[1].size == b.size);

    auto result = setisfy(places);
    REQUIRE(result.contains(glm::dvec2(1, 0)));
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
    auto places = RTSPathingLib::FormationCalculator(formation, input).calculate();

    REQUIRE(places.size() == input.size());
  }

  TEST_CASE("Formation/InterfacePoint", "[FormationSingle]") {
    RTSPathingLib::Body b;
    b.category = 0;
    b.size = 1;
    b.position = glm::dvec2(99, 99);

    std::vector<RTSPathingLib::Body> input = { b };
    RTSPathingLib::Formation formation;
    formation.setOwnInterfacePoint((int)RTSPathingLib::RectangleInterfacePoint::Top);
    formation.setShape(std::make_unique<RTSPathingLib::RectangleFormationShape>());
    auto places = RTSPathingLib::FormationCalculator(formation, input).calculate();

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
    formation.setOwnInterfacePoint((int)RTSPathingLib::RectangleInterfacePoint::Top);
    formation.setRotation(glm::pi<double>());
    formation.setShape(std::make_unique<RTSPathingLib::RectangleFormationShape>());
    auto places = RTSPathingLib::FormationCalculator(formation, input).calculate();

    REQUIRE(places.size() == input.size());
    REQUIRE(places[0].category == b.category);
    REQUIRE(places[0].size == b.size);
    REQUIRE(places[0].position.x != 99);
    REQUIRE(places[0].position.y != 99);
  }


  TEST_CASE("Formation/RotationWithInterface", "[FormationSingle]") {
    RTSPathingLib::Body a;
    a.category = 0;
    a.size = 1;
    a.position = glm::dvec2(99, 99);
    RTSPathingLib::Body b;
    b.category = 1;
    b.size = 1;
    b.position = glm::dvec2(99, 99);

    std::vector<RTSPathingLib::Body> input = { a,a,a,a,b,b,b,b };
    RTSPathingLib::Formation formation;
    formation.setOwnInterfacePoint((int)RTSPathingLib::TriangleInterfacePoint::LeftMiddle);
    formation.setRotation(glm::pi<double>());
    formation.setShape(std::make_unique<RTSPathingLib::TriangleFormationShape>());


    std::unique_ptr<RTSPathingLib::Formation> formation2 = std::make_unique<RTSPathingLib::Formation>();
    formation2->setShape(std::make_unique<RTSPathingLib::RectangleFormationShape>());
    formation2->setUnitCategory(1);
    formation2->setParentInterfacePoint((int)RTSPathingLib::TriangleInterfacePoint::LeftMiddle);
    formation2->setOwnInterfacePoint((int)RTSPathingLib::RectangleInterfacePoint::Top);
    formation2->setRotateWithInterface(true);
    formation.addChild(std::move(formation2));

    auto places = RTSPathingLib::FormationCalculator(formation, input).calculate();

    REQUIRE(places.size() == input.size());

    auto categories = countCategories(places);
    REQUIRE(categories[0] == 4);
    REQUIRE(categories[1] == 4);

    auto result = setisfy(places);
    REQUIRE(result.contains(glm::dvec2(0, 0)));
    REQUIRE(result.contains(glm::dvec2(0, 1)));
    REQUIRE(result.contains(glm::dvec2(0, 2)));
    REQUIRE(result.contains(glm::dvec2(1, 1)));
    REQUIRE(result.contains(glm::dvec2(1, 2)));
    REQUIRE(result.contains(glm::dvec2(1, 3)));
    REQUIRE(result.contains(glm::dvec2(2, 1)));
    REQUIRE(result.contains(glm::dvec2(2, 2)));
  }

  TEST_CASE("Formation/InterfaceWidth", "[FormationSingle]") {
    RTSPathingLib::Body a;
    a.category = 0;
    a.size = 1;
    a.position = glm::dvec2(99, 99);
    RTSPathingLib::Body b;
    b.category = 1;
    b.size = 1;
    b.position = glm::dvec2(99, 99);

    std::vector<RTSPathingLib::Body> input = { a,a,a,a,b,b,b,b,b,b,b,b };
    RTSPathingLib::Formation formation;
    formation.setOwnInterfacePoint((int)RTSPathingLib::TriangleInterfacePoint::Center);
    formation.setRotation(glm::pi<double>());
    formation.setShape(std::make_unique<RTSPathingLib::TriangleFormationShape>());


    std::unique_ptr<RTSPathingLib::Formation> formation2 = std::make_unique<RTSPathingLib::Formation>();
    formation2->setShape(std::make_unique<RTSPathingLib::RectangleFormationShape>());
    formation2->setUnitCategory(1);
    formation2->setParentInterfacePoint((int)RTSPathingLib::TriangleInterfacePoint::RightMiddle);
    formation2->setOwnInterfacePoint((int)RTSPathingLib::RectangleInterfacePoint::Top);
    formation2->setRotateWithInterface(true);
    formation2->setOverwriteWidthWithInterfaceWidth(true);
    formation2->getShape().setBaseSize(glm::dvec2(5, 0.1));
    formation.addChild(std::move(formation2));

    auto places = RTSPathingLib::FormationCalculator(formation, input).calculate();

    REQUIRE(places.size() == input.size());

    auto categories = countCategories(places);
    REQUIRE(categories[0] == 4);
    REQUIRE(categories[1] == 8);

    auto result = setisfy(places);
    REQUIRE(result.contains(glm::dvec2(0, 0)));
    REQUIRE(result.contains(glm::dvec2(0, 1)));
    REQUIRE(result.contains(glm::dvec2(1, -1)));
    REQUIRE(result.contains(glm::dvec2(1, 0)));
    REQUIRE(result.contains(glm::dvec2(1, 1)));
    REQUIRE(result.contains(glm::dvec2(2, -1)));
    REQUIRE(result.contains(glm::dvec2(2, 0)));
    REQUIRE(result.contains(glm::dvec2(2, 1)));
    REQUIRE(result.contains(glm::dvec2(3, -1)));
    REQUIRE(result.contains(glm::dvec2(3, 0)));
    REQUIRE(result.contains(glm::dvec2(3, 1)));
    REQUIRE(result.contains(glm::dvec2(4, 1)));

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
    formation2->setParentInterfacePoint((int)RTSPathingLib::RectangleInterfacePoint::Bottom);
    formation2->setOwnInterfacePoint((int)RTSPathingLib::RectangleInterfacePoint::Top);
    formation.addChild(std::move(formation2));

    auto places = RTSPathingLib::FormationCalculator(formation, input).calculate();

    REQUIRE(places.size() == input.size());


    auto categories = countCategories(places);
    REQUIRE(categories[0] == 2);
    REQUIRE(categories[1] == 4);

    auto result = setisfy(places);
    REQUIRE(result.contains(glm::dvec2(0, 0)));
    REQUIRE(result.contains(glm::dvec2(0, 1)));
    REQUIRE(result.contains(glm::dvec2(0, 2)));
    REQUIRE(result.contains(glm::dvec2(1, 0)));
    REQUIRE(result.contains(glm::dvec2(1, 1)));
    REQUIRE(result.contains(glm::dvec2(1, 2)));

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
    formation2->setParentInterfacePoint((int)RTSPathingLib::RectangleInterfacePoint::Bottom);
    formation2->setOwnInterfacePoint((int)RTSPathingLib::RectangleInterfacePoint::Top);
    formation.addChild(std::move(formation2));

    auto places = RTSPathingLib::FormationCalculator(formation, input).calculate();

    REQUIRE(places.size() == input.size());

    auto categories = countCategories(places);
    REQUIRE(categories[0] == 4);
    REQUIRE(categories[1] == 4);

    auto result = setisfy(places);
    REQUIRE(result.contains(glm::dvec2(0, 0)));
    REQUIRE(result.contains(glm::dvec2(0, 1)));
    REQUIRE(result.contains(glm::dvec2(0, 2)));
    REQUIRE(result.contains(glm::dvec2(0, 3)));
    REQUIRE(result.contains(glm::dvec2(1, 0)));
    REQUIRE(result.contains(glm::dvec2(1, 1)));
    REQUIRE(result.contains(glm::dvec2(1, 2)));
    REQUIRE(result.contains(glm::dvec2(1, 3)));
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

    std::vector<RTSPathingLib::Body> input = { a,a, a, b, b, b, b, b, b, b, b, b };
    RTSPathingLib::Formation formation;
    formation.setShape(std::make_unique<RTSPathingLib::RectangleFormationShape>());
    formation.setUnitCategory(0);

    std::unique_ptr<RTSPathingLib::Formation> formation2 = std::make_unique<RTSPathingLib::Formation>();
    formation2->setShape(std::make_unique<RTSPathingLib::RectangleFormationShape>());
    formation2->setUnitCategory(1);
    formation2->setParentInterfacePoint((int)RTSPathingLib::RectangleInterfacePoint::Top);
    formation2->setOwnInterfacePoint((int)RTSPathingLib::RectangleInterfacePoint::Top);
    formation.addChild(std::move(formation2));

    auto places = RTSPathingLib::FormationCalculator(formation, input).calculate();

    REQUIRE(places.size() == input.size());


    auto categories = countCategories(places);
    REQUIRE(categories[0] == 3);
    REQUIRE(categories[1] == 9);

    auto result = setisfy(places);
    REQUIRE(result.contains(glm::dvec2(0, 0)));
    REQUIRE(result.contains(glm::dvec2(0, 1)));
    REQUIRE(result.contains(glm::dvec2(0, 2)));
    REQUIRE(result.contains(glm::dvec2(1, 0)));
    REQUIRE(result.contains(glm::dvec2(1, 1)));
    REQUIRE(result.contains(glm::dvec2(1, 2)));
    REQUIRE(result.contains(glm::dvec2(2, 0)));
    REQUIRE(result.contains(glm::dvec2(2, 1)));
    REQUIRE(result.contains(glm::dvec2(2, 2)));
    REQUIRE(result.contains(glm::dvec2(3, 0)));
    REQUIRE(result.contains(glm::dvec2(3, 1)));
    REQUIRE(result.contains(glm::dvec2(3, 2)));
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

    std::vector<RTSPathingLib::Body> input = { a,a, a, b, b, b, };
    RTSPathingLib::Formation formation;
    formation.setShape(std::make_unique<RTSPathingLib::RectangleFormationShape>());
    formation.setUnitCategory(0);

    std::unique_ptr<RTSPathingLib::Formation> formation2 = std::make_unique<RTSPathingLib::Formation>();
    formation2->setShape(std::make_unique<RTSPathingLib::RectangleFormationShape>());
    formation2->setUnitCategory(1);
    formation2->setParentInterfacePoint((int)RTSPathingLib::RectangleInterfacePoint::Top);
    formation2->setOwnInterfacePoint((int)RTSPathingLib::RectangleInterfacePoint::Bottom);
    formation2->setRotation(glm::pi<float>() * 0.5);
    formation.addChild(std::move(formation2));

    auto places = RTSPathingLib::FormationCalculator(formation, input).calculate();


    auto categories = countCategories(places);
    REQUIRE(categories[0] == 3);
    REQUIRE(categories[1] == 3);

    REQUIRE(places.size() == input.size());

    auto result = setisfy(places);
    REQUIRE(result.contains(glm::dvec2(0, 0)));
    REQUIRE(result.contains(glm::dvec2(0, 1)));
    REQUIRE(result.contains(glm::dvec2(1, -1)));
    REQUIRE(result.contains(glm::dvec2(1, 0)));
    REQUIRE(result.contains(glm::dvec2(1, 1)));
    REQUIRE(result.contains(glm::dvec2(2, -1)));
  }

  TEST_CASE("Formation/ChildDepth2", "[FormationSingle]") {
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

    std::vector<RTSPathingLib::Body> input = { a, a, b,b,b,b,c, c,c, c };
    RTSPathingLib::Formation formation;
    formation.setShape(std::make_unique<RTSPathingLib::RectangleFormationShape>());
    formation.setUnitCategory(0);

    std::unique_ptr<RTSPathingLib::Formation> formation2 = std::make_unique<RTSPathingLib::Formation>();

    std::unique_ptr<RTSPathingLib::Formation> formation3 = std::make_unique<RTSPathingLib::Formation>();
    formation3->setShape(std::make_unique<RTSPathingLib::TriangleFormationShape>());
    formation3->setUnitCategory(2);
    formation3->setParentInterfacePoint((int)RTSPathingLib::RectangleInterfacePoint::Top);
    formation3->setOwnInterfacePoint((int)RTSPathingLib::TriangleInterfacePoint::BottomCenter);
    formation2->addChild(std::move(formation3));

    formation2->setShape(std::make_unique<RTSPathingLib::RectangleFormationShape>());
    formation2->setUnitCategory(1);
    formation2->setParentInterfacePoint((int)RTSPathingLib::RectangleInterfacePoint::Top);
    formation2->setOwnInterfacePoint((int)RTSPathingLib::RectangleInterfacePoint::Bottom);
    formation.addChild(std::move(formation2));

    auto places = RTSPathingLib::FormationCalculator(formation, input).calculate();

    auto categories = countCategories(places);
    REQUIRE(categories[0] == 2);
    REQUIRE(categories[1] == 4);
    REQUIRE(categories[2] == 4);

    auto result = setisfy(places);
    REQUIRE(result.contains(glm::dvec2(0, 0)));
    REQUIRE(result.contains(glm::dvec2(0, 1)));
    REQUIRE(result.contains(glm::dvec2(0, 2)));
    REQUIRE(result.contains(glm::dvec2(0, 3)));
    REQUIRE(result.contains(glm::dvec2(0, 4)));
    REQUIRE(result.contains(glm::dvec2(1, 0)));
    REQUIRE(result.contains(glm::dvec2(1, 1)));
    REQUIRE(result.contains(glm::dvec2(1, 2)));
    REQUIRE(result.contains(glm::dvec2(1, 3)));
    REQUIRE(result.contains(glm::dvec2(1, 4)));
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
    for (size_t i = 0; i < 70; i++)
      input.push_back(b);
    for (size_t i = 0; i < 50; i++)
      input.push_back(c);
    RTSPathingLib::Formation formation;
    formation.setShape(std::make_unique<RTSPathingLib::ArcFormationShape>());
    formation.setUnitCategory(0);

    std::unique_ptr<RTSPathingLib::Formation> spike = std::make_unique<RTSPathingLib::Formation>();
    spike->setShape(std::make_unique<RTSPathingLib::TriangleFormationShape>());
    spike->setUnitCategory(2);
    spike->setOwnInterfacePoint((int)RTSPathingLib::TriangleInterfacePoint::BottomCenter);
    spike->setParentInterfacePoint(1);

    std::unique_ptr<RTSPathingLib::Formation> spike2 = std::make_unique<RTSPathingLib::Formation>();
    spike2->setShape(std::make_unique<RTSPathingLib::TriangleFormationShape>());
    spike2->setUnitCategory(2);
    spike2->setOwnInterfacePoint((int)RTSPathingLib::TriangleInterfacePoint::BottomCenter);
    spike2->setParentInterfacePoint(10);
    spike2->setRotation(-glm::pi<double>() * 0.5);

    std::unique_ptr<RTSPathingLib::Formation> spike3 = std::make_unique<RTSPathingLib::Formation>();
    spike3->setShape(std::make_unique<RTSPathingLib::TriangleFormationShape>());
    spike3->setUnitCategory(2);
    spike3->setOwnInterfacePoint((int)RTSPathingLib::TriangleInterfacePoint::BottomCenter);
    spike3->setParentInterfacePoint(27);
    spike3->setRotation(glm::pi<double>() * 0.5);

    std::unique_ptr<RTSPathingLib::Formation> spike4 = std::make_unique<RTSPathingLib::Formation>();
    spike4->setShape(std::make_unique<RTSPathingLib::TriangleFormationShape>());
    spike4->setUnitCategory(2);
    spike4->setOwnInterfacePoint((int)RTSPathingLib::TriangleInterfacePoint::BottomCenter);
    spike4->setParentInterfacePoint(18);
    spike4->setRotation(glm::pi<double>());

    std::unique_ptr<RTSPathingLib::Formation> formation2 = std::make_unique<RTSPathingLib::Formation>();
    formation2->addChild(std::move(spike));
    formation2->addChild(std::move(spike2));
    formation2->addChild(std::move(spike3));
    formation2->addChild(std::move(spike4));
    formation2->setShape(std::make_unique<RTSPathingLib::ArcFormationShape>());
    formation2->setUnitCategory(1);
    formation.addChild(std::move(formation2));

    auto places = RTSPathingLib::FormationCalculator(formation, input).calculate();

    REQUIRE(places.size() == input.size());

    auto categories = countCategories(places);
    REQUIRE(categories[0] == 30);
    REQUIRE(categories[1] == 70);
    REQUIRE(categories[2] == 50);
  }
}