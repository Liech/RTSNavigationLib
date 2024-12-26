#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <set>

#include <RTSNavigationLib/Body.h>
#include "RTSNavigationLib/Formation/FormationCalculator.h"
#include "RTSNavigationLib/Formation/Formation.h"
#include "RTSNavigationLib/Formation/FormationShape/RectangleFormationShape.h"
#include "RTSNavigationLib/Formation/FormationShape/ArcFormationShape.h"
#include "RTSNavigationLib/Formation/FormationShape/TriangleFormationShape.h"
#include "RTSNavigationLib/Formation/FormationShape/RectangleInterfacePoint.h"
#include "RTSNavigationLib/Formation/FormationShape/TriangleInterfacePoint.h"

namespace FormationTests {
  struct lex_compare {
    bool operator() (const glm::dvec2& lhs, const glm::dvec2& rhs) const {
      return (lhs.x < rhs.x) || (lhs.x == rhs.x && lhs.y < rhs.y);
    }
  };

  glm::dvec2 getFirstPlace(std::vector<RTSNavigationLib::WorldBody> places) {
    glm::dvec2 first = glm::dvec2(std::numeric_limits<double>().max(), std::numeric_limits<double>().max());
    for (auto& x : places)
      if (lex_compare()(x.position, first))
        first = x.position;
    return first;
  }
  std::set<glm::dvec2, lex_compare> setisfy(const std::vector<RTSNavigationLib::WorldBody>& places)
  {
    auto first = getFirstPlace(places);
    std::set<glm::dvec2, lex_compare> result;
    for (auto& x : places) {
      glm::dvec2 v = x.position - first;
      v[0] = std::round(v.x);
      v[1] = std::round(v.y);
      result.insert(v);
    }
    return result;
  }

  std::map<size_t, size_t> countCategories(const std::vector<RTSNavigationLib::WorldBody>& places) {
    std::map<size_t, size_t> result;
    for (auto& x : places) {
      if (result.count(x.category) == 0)
        result[x.category] = 0;
      result[x.category]++;
    }
    return result;
  }


  TEST_CASE("Formation/RectangleSingle") {
      RTSNavigationLib::Body b;
    b.category = 0;
    b.size = 1;

    std::vector<RTSNavigationLib::Body> input = { b };
    RTSNavigationLib::Formation formation;
    formation.setShape(std::make_unique<RTSNavigationLib::RectangleFormationShape>());
    auto places = RTSNavigationLib::FormationCalculator(formation, input).calculate();

    REQUIRE(places.size() == input.size());
    REQUIRE(places[0].category == b.category);
    REQUIRE(places[0].size == b.size);
  }

  TEST_CASE("Formation/RectangleDouble") {
    RTSNavigationLib::Body b;
    b.category = 0;
    b.size = 1;

    std::vector<RTSNavigationLib::Body> input = { b, b };
    RTSNavigationLib::Formation formation;
    formation.setShape(std::make_unique<RTSNavigationLib::RectangleFormationShape>());
    auto places = RTSNavigationLib::FormationCalculator(formation, input).calculate();

    REQUIRE(places.size() == input.size());
    REQUIRE(places[0].category == b.category);
    REQUIRE(places[0].size == b.size);
    REQUIRE(places[1].category == b.category);
    REQUIRE(places[1].size == b.size);

    auto result = setisfy(places);
    REQUIRE(result.contains(glm::dvec2(1, 0)));
  }

  TEST_CASE("Formation/RectangleMany") {
    RTSNavigationLib::Body b;
    b.category = 0;
    b.size = 1;

    std::vector<RTSNavigationLib::Body> input = { };
    for (int i = 0; i < 16; i++)
      input.push_back(b);
    RTSNavigationLib::Formation formation;
    formation.setShape(std::make_unique<RTSNavigationLib::RectangleFormationShape>());
    auto places = RTSNavigationLib::FormationCalculator(formation, input).calculate();

    REQUIRE(places.size() == input.size());
  }

  TEST_CASE("Formation/ArcSingle") {
    RTSNavigationLib::Body b;
    b.category = 0;
    b.size = 1;

    std::vector<RTSNavigationLib::Body> input = { b };
    RTSNavigationLib::Formation formation;
    formation.setShape(std::make_unique<RTSNavigationLib::ArcFormationShape>());
    auto places = RTSNavigationLib::FormationCalculator(formation, input).calculate();

    REQUIRE(places.size() == input.size());
    REQUIRE(places[0].category == b.category);
    REQUIRE(places[0].size == b.size);
    REQUIRE(places[0].position.x != 99);
    REQUIRE(places[0].position.y != 99);
  }

  TEST_CASE("Formation/ArcDouble") {
    RTSNavigationLib::Body b;
    b.category = 0;
    b.size = 1;

    std::vector<RTSNavigationLib::Body> input = { b, b };
    RTSNavigationLib::Formation formation;
    formation.setShape(std::make_unique<RTSNavigationLib::ArcFormationShape>());
    auto places = RTSNavigationLib::FormationCalculator(formation, input).calculate();

    REQUIRE(places.size() == input.size());
    REQUIRE(places[0].category == b.category);
    REQUIRE(places[0].size == b.size);
    REQUIRE(places[1].category == b.category);
    REQUIRE(places[1].size == b.size);

    auto result = setisfy(places);
    REQUIRE(result.contains(glm::dvec2(1, 0)));
  }

  TEST_CASE("Formation/ArcMany") {
    RTSNavigationLib::Body b;
    b.category = 0;
    b.size = 1;

    std::vector<RTSNavigationLib::Body> input = { };
    for (int i = 0; i < 16; i++)
      input.push_back(b);
    RTSNavigationLib::Formation formation;
    formation.setShape(std::make_unique<RTSNavigationLib::ArcFormationShape>());
    auto places = RTSNavigationLib::FormationCalculator(formation, input).calculate();

    REQUIRE(places.size() == input.size());
  }

  TEST_CASE("Formation/PartialArc") {
    RTSNavigationLib::Body b;
    b.category = 0;
    b.size = 1;

    std::vector<RTSNavigationLib::Body> input = { };
    for (int i = 0; i < 16; i++)
      input.push_back(b);
    RTSNavigationLib::Formation formation;
    auto shape = std::make_unique<RTSNavigationLib::ArcFormationShape>();
    shape->setArcAngle(glm::pi<double>() * 1);
    formation.setShape(std::move(shape));
    auto places = RTSNavigationLib::FormationCalculator(formation, input).calculate();

    REQUIRE(places.size() == input.size());
  }

  TEST_CASE("Formation/TriangleSingle") {
    RTSNavigationLib::Body b;
    b.category = 0;
    b.size = 1;

    std::vector<RTSNavigationLib::Body> input = { b };
    RTSNavigationLib::Formation formation;
    formation.setShape(std::make_unique<RTSNavigationLib::TriangleFormationShape>());
    auto places = RTSNavigationLib::FormationCalculator(formation, input).calculate();

    REQUIRE(places.size() == input.size());
    REQUIRE(places[0].category == b.category);
    REQUIRE(places[0].size == b.size);
    REQUIRE(places[0].position.x != 99);
    REQUIRE(places[0].position.y != 99);
  }

  TEST_CASE("Formation/TriangleDouble") {
    RTSNavigationLib::Body b;
    b.category = 0;
    b.size = 1;

    std::vector<RTSNavigationLib::Body> input = { b, b };
    RTSNavigationLib::Formation formation;
    formation.setShape(std::make_unique<RTSNavigationLib::TriangleFormationShape>());
    auto places = RTSNavigationLib::FormationCalculator(formation, input).calculate();

    REQUIRE(places.size() == input.size());
    REQUIRE(places[0].category == b.category);
    REQUIRE(places[0].size == b.size);
    REQUIRE(places[1].category == b.category);
    REQUIRE(places[1].size == b.size);

    auto result = setisfy(places);
    REQUIRE(result.contains(glm::dvec2(1, 0)));
  }

  TEST_CASE("Formation/TriangleMany") {
    RTSNavigationLib::Body b;
    b.category = 0;
    b.size = 1;

    std::vector<RTSNavigationLib::Body> input = { };
    for (int i = 0; i < 16; i++)
      input.push_back(b);
    RTSNavigationLib::Formation formation;
    formation.setShape(std::make_unique<RTSNavigationLib::TriangleFormationShape>());
    auto places = RTSNavigationLib::FormationCalculator(formation, input).calculate();

    REQUIRE(places.size() == input.size());
  }

  TEST_CASE("Formation/HollowArc") {
    RTSNavigationLib::Body b;
    b.category = 0;
    b.size = 1;

    std::vector<RTSNavigationLib::Body> input = { };
    for (int i = 0; i < 8; i++)
      input.push_back(b);
    RTSNavigationLib::Formation formation;
    formation.setShape(std::make_unique<RTSNavigationLib::ArcFormationShape>());
    formation.getShape().setHollow(0.4);
    auto places = RTSNavigationLib::FormationCalculator(formation, input).calculate();

    REQUIRE(places.size() == input.size());
    
    auto result = setisfy(places);
    REQUIRE(result.contains(glm::dvec2(0, 0)));
    REQUIRE(result.contains(glm::dvec2(0, 1)));
    REQUIRE(result.contains(glm::dvec2(1,-1)));
    REQUIRE(result.contains(glm::dvec2(1, 2)));
    REQUIRE(result.contains(glm::dvec2(2,-1)));
    REQUIRE(result.contains(glm::dvec2(2, 2)));
    REQUIRE(result.contains(glm::dvec2(3, 0)));
    REQUIRE(result.contains(glm::dvec2(3, 1)));

  }

  TEST_CASE("Formation/InterfacePoint") {
    RTSNavigationLib::Body b;
    b.category = 0;
    b.size = 1;

    std::vector<RTSNavigationLib::Body> input = { b };
    RTSNavigationLib::Formation formation;
    formation.setOwnInterfacePoint((int)RTSNavigationLib::RectangleInterfacePoint::Top);
    formation.setShape(std::make_unique<RTSNavigationLib::RectangleFormationShape>());
    auto places = RTSNavigationLib::FormationCalculator(formation, input).calculate();

    REQUIRE(places.size() == input.size());
    REQUIRE(places[0].category == b.category);
    REQUIRE(places[0].size == b.size);
    REQUIRE(places[0].position.x != 99);
    REQUIRE(places[0].position.y != 99);
  }

  TEST_CASE("Formation/Rotation") {
    RTSNavigationLib::Body b;
    b.category = 0;
    b.size = 1;

    std::vector<RTSNavigationLib::Body> input = { b };
    RTSNavigationLib::Formation formation;
    formation.setOwnInterfacePoint((int)RTSNavigationLib::RectangleInterfacePoint::Top);
    formation.setRotation(glm::pi<double>());
    formation.setShape(std::make_unique<RTSNavigationLib::RectangleFormationShape>());
    auto places = RTSNavigationLib::FormationCalculator(formation, input).calculate();

    REQUIRE(places.size() == input.size());
    REQUIRE(places[0].category == b.category);
    REQUIRE(places[0].size == b.size);
    REQUIRE(places[0].position.x != 99);
    REQUIRE(places[0].position.y != 99);
  }


  TEST_CASE("Formation/RotationWithInterface") {
    RTSNavigationLib::Body a;
    a.category = 0;
    a.size = 1;
    RTSNavigationLib::Body b;
    b.category = 1;
    b.size = 1;

    std::vector<RTSNavigationLib::Body> input = { a,a,a,a,b,b,b,b };
    RTSNavigationLib::Formation formation;
    formation.setOwnInterfacePoint((int)RTSNavigationLib::TriangleInterfacePoint::LeftMiddle);
    formation.setRotation(glm::pi<double>());
    formation.setShape(std::make_unique<RTSNavigationLib::TriangleFormationShape>());


    std::unique_ptr<RTSNavigationLib::Formation> formation2 = std::make_unique<RTSNavigationLib::Formation>();
    formation2->setShape(std::make_unique<RTSNavigationLib::RectangleFormationShape>());
    formation2->setUnitCategories({ 1 });
    formation2->setParentInterfacePoint((int)RTSNavigationLib::TriangleInterfacePoint::LeftMiddle);
    formation2->setOwnInterfacePoint((int)RTSNavigationLib::RectangleInterfacePoint::Top);
    formation2->setRotateWithInterface(true);
    formation.addChild(std::move(formation2));

    auto places = RTSNavigationLib::FormationCalculator(formation, input).calculate();

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
    REQUIRE(result.contains(glm::dvec2(2, 2)));
    REQUIRE(result.contains(glm::dvec2(2, 3)));
  }

  TEST_CASE("Formation/InterfaceWidth") {
    RTSNavigationLib::Body a;
    a.category = 0;
    a.size     = 1;
    RTSNavigationLib::Body b;
    b.category = 1;
    b.size = 1;

    std::vector<RTSNavigationLib::Body> input = { a,a,a,a,b,b,b,b,b,b,b,b };
    RTSNavigationLib::Formation formation;
    formation.setOwnInterfacePoint((int)RTSNavigationLib::TriangleInterfacePoint::Center);
    formation.setRotation(glm::pi<double>());
    formation.setShape(std::make_unique<RTSNavigationLib::TriangleFormationShape>());


    std::unique_ptr<RTSNavigationLib::Formation> formation2 = std::make_unique<RTSNavigationLib::Formation>();
    formation2->setShape(std::make_unique<RTSNavigationLib::RectangleFormationShape>());
    formation2->setUnitCategories({ 1 });
    formation2->setParentInterfacePoint((int)RTSNavigationLib::TriangleInterfacePoint::RightMiddle);
    formation2->setOwnInterfacePoint((int)RTSNavigationLib::RectangleInterfacePoint::Top);
    formation2->setRotateWithInterface(true);
    formation2->setOverwriteWidthWithInterfaceWidth(true);
    formation2->getShape().setBaseSize(glm::dvec2(5, 0.1));
    formation.addChild(std::move(formation2));

    auto places = RTSNavigationLib::FormationCalculator(formation, input).calculate();

    REQUIRE(places.size() == input.size());

    auto categories = countCategories(places);
    REQUIRE(categories[0] == 4);
    REQUIRE(categories[1] == 8);

    auto result = setisfy(places);
    REQUIRE(result.contains(glm::dvec2(0, 0)));
    REQUIRE(result.contains(glm::dvec2(0, 1)));
    REQUIRE(result.contains(glm::dvec2(1,-2)));
    REQUIRE(result.contains(glm::dvec2(1,-1)));
    REQUIRE(result.contains(glm::dvec2(1, 0)));
    REQUIRE(result.contains(glm::dvec2(1, 1)));
    REQUIRE(result.contains(glm::dvec2(2,-2)));
    REQUIRE(result.contains(glm::dvec2(2,-1)));
    REQUIRE(result.contains(glm::dvec2(2, 0)));
    REQUIRE(result.contains(glm::dvec2(2, 1)));
    REQUIRE(result.contains(glm::dvec2(3,-1)));
    REQUIRE(result.contains(glm::dvec2(3, 0)));

  }

  TEST_CASE("Formation/OneChild") {
    RTSNavigationLib::Body a;
    a.category = 0;
    a.size = 1;
    RTSNavigationLib::Body b;
    b.category = 1;
    b.size = 1;

    std::vector<RTSNavigationLib::Body> input = { a, a, b, b, b, b };
    RTSNavigationLib::Formation formation;
    formation.setShape(std::make_unique<RTSNavigationLib::RectangleFormationShape>());
    formation.setUnitCategories({ 0 });

    std::unique_ptr<RTSNavigationLib::Formation> formation2 = std::make_unique<RTSNavigationLib::Formation>();
    formation2->setShape(std::make_unique<RTSNavigationLib::RectangleFormationShape>());
    formation2->setUnitCategories({ 1 });
    formation2->setParentInterfacePoint((int)RTSNavigationLib::RectangleInterfacePoint::Bottom);
    formation2->setOwnInterfacePoint((int)RTSNavigationLib::RectangleInterfacePoint::Top);
    formation.addChild(std::move(formation2));

    auto places = RTSNavigationLib::FormationCalculator(formation, input).calculate();

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

  TEST_CASE("Formation/OneChild2") {
    RTSNavigationLib::Body a;
    a.category = 0;
    a.size = 1;
    RTSNavigationLib::Body b;
    b.category = 1;
    b.size = 1;

    std::vector<RTSNavigationLib::Body> input = { a, a, a, a, b, b, b, b };
    RTSNavigationLib::Formation formation;
    formation.setShape(std::make_unique<RTSNavigationLib::RectangleFormationShape>());
    formation.setUnitCategories({0});

    std::unique_ptr<RTSNavigationLib::Formation> formation2 = std::make_unique<RTSNavigationLib::Formation>();
    formation2->setShape(std::make_unique<RTSNavigationLib::RectangleFormationShape>());
    formation2->setUnitCategories({ 1 });
    formation2->setParentInterfacePoint((int)RTSNavigationLib::RectangleInterfacePoint::Bottom);
    formation2->setOwnInterfacePoint((int)RTSNavigationLib::RectangleInterfacePoint::Top);
    formation.addChild(std::move(formation2));

    auto places = RTSNavigationLib::FormationCalculator(formation, input).calculate();

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


  TEST_CASE("Formation/OverlappingChild") {
    RTSNavigationLib::Body a;
    a.category = 0;
    a.size = 1;
    RTSNavigationLib::Body b;
    b.category = 1;
    b.size = 1;

    std::vector<RTSNavigationLib::Body> input = { a,a, a, b, b, b, b, b, b, b, b, b };
    RTSNavigationLib::Formation formation;
    formation.setShape(std::make_unique<RTSNavigationLib::RectangleFormationShape>());
    formation.setUnitCategories({ 0 });

    std::unique_ptr<RTSNavigationLib::Formation> formation2 = std::make_unique<RTSNavigationLib::Formation>();
    formation2->setShape(std::make_unique<RTSNavigationLib::RectangleFormationShape>());
    formation2->setUnitCategories({ 1 });
    formation2->setParentInterfacePoint((int)RTSNavigationLib::RectangleInterfacePoint::Top);
    formation2->setOwnInterfacePoint((int)RTSNavigationLib::RectangleInterfacePoint::Top);
    formation.addChild(std::move(formation2));

    auto places = RTSNavigationLib::FormationCalculator(formation, input).calculate();

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

  TEST_CASE("Formation/RotateChild") {
    RTSNavigationLib::Body a;
    a.category = 0;
    a.size = 1;
    RTSNavigationLib::Body b;
    b.category = 1;
    b.size = 1;

    std::vector<RTSNavigationLib::Body> input = { a,a, a, b, b, b, };
    RTSNavigationLib::Formation formation;
    formation.setShape(std::make_unique<RTSNavigationLib::RectangleFormationShape>());
    formation.setUnitCategories({ 0 });

    std::unique_ptr<RTSNavigationLib::Formation> formation2 = std::make_unique<RTSNavigationLib::Formation>();
    formation2->setShape(std::make_unique<RTSNavigationLib::RectangleFormationShape>());
    formation2->setUnitCategories({ 1 });
    formation2->setParentInterfacePoint((int)RTSNavigationLib::RectangleInterfacePoint::Top);
    formation2->setOwnInterfacePoint((int)RTSNavigationLib::RectangleInterfacePoint::Bottom);
    formation2->setRotation(glm::pi<float>() * 0.5);
    formation.addChild(std::move(formation2));

    auto places = RTSNavigationLib::FormationCalculator(formation, input).calculate();


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

  TEST_CASE("Formation/ChildDepth2") {
    RTSNavigationLib::Body a;
    a.category = 0;
    a.size = 1;
    RTSNavigationLib::Body b;
    b.category = 1;
    b.size = 1;
    RTSNavigationLib::Body c;
    c.category = 2;
    c.size = 1;

    std::vector<RTSNavigationLib::Body> input = { a, a, b,b,b,b,c, c,c, c };
    RTSNavigationLib::Formation formation;
    formation.setShape(std::make_unique<RTSNavigationLib::RectangleFormationShape>());
    formation.setUnitCategories({ 0 });

    std::unique_ptr<RTSNavigationLib::Formation> formation2 = std::make_unique<RTSNavigationLib::Formation>();

    std::unique_ptr<RTSNavigationLib::Formation> formation3 = std::make_unique<RTSNavigationLib::Formation>();
    formation3->setShape(std::make_unique<RTSNavigationLib::TriangleFormationShape>());
    formation3->setUnitCategories({ 2 });
    formation3->setParentInterfacePoint((int)RTSNavigationLib::RectangleInterfacePoint::Top);
    formation3->setOwnInterfacePoint((int)RTSNavigationLib::TriangleInterfacePoint::BottomCenter);
    formation2->addChild(std::move(formation3));

    formation2->setShape(std::make_unique<RTSNavigationLib::RectangleFormationShape>());
    formation2->setUnitCategories({ 1 });
    formation2->setParentInterfacePoint((int)RTSNavigationLib::RectangleInterfacePoint::Top);
    formation2->setOwnInterfacePoint((int)RTSNavigationLib::RectangleInterfacePoint::Bottom);
    formation.addChild(std::move(formation2));

    auto places = RTSNavigationLib::FormationCalculator(formation, input).calculate();

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

  TEST_CASE("Formation/PraiseTheSun") {

    RTSNavigationLib::Body a;
    a.category = 0;
    a.size = 1;
    RTSNavigationLib::Body a2;
    a2.category = 0;
    a2.size = 2;
    RTSNavigationLib::Body b;
    b.category = 1;
    b.size = 1;
    RTSNavigationLib::Body c;
    c.category = 2;
    c.size = 1;

    std::vector<RTSNavigationLib::Body> input;
    for (size_t i = 0; i < 300; i++)
      input.push_back(a);
    for (size_t i = 0; i < 50; i++)
      input.push_back(a2);
    for (size_t i = 0; i < 700; i++)
      input.push_back(b);
    for (size_t i = 0; i < 500; i++)
      input.push_back(c);
    RTSNavigationLib::Formation formation;
    formation.setShape(std::make_unique<RTSNavigationLib::ArcFormationShape>());
    formation.setUnitCategories({ 0 });

    std::unique_ptr<RTSNavigationLib::Formation> spike = std::make_unique<RTSNavigationLib::Formation>();
    spike->setShape(std::make_unique<RTSNavigationLib::TriangleFormationShape>());
    spike->setUnitCategories({ 2 });
    spike->setOwnInterfacePoint((int)RTSNavigationLib::TriangleInterfacePoint::BottomCenter);
    spike->setParentInterfacePoint(1);

    std::unique_ptr<RTSNavigationLib::Formation> spike2 = std::make_unique<RTSNavigationLib::Formation>();
    spike2->setShape(std::make_unique<RTSNavigationLib::TriangleFormationShape>());
    spike2->setUnitCategories({ 2 });
    spike2->setOwnInterfacePoint((int)RTSNavigationLib::TriangleInterfacePoint::BottomCenter);
    spike2->setParentInterfacePoint(10);
    spike2->setRotation(-glm::pi<double>() * 0.5);

    std::unique_ptr<RTSNavigationLib::Formation> spike3 = std::make_unique<RTSNavigationLib::Formation>();
    spike3->setShape(std::make_unique<RTSNavigationLib::TriangleFormationShape>());
    spike3->setUnitCategories({ 2 });
    spike3->setOwnInterfacePoint((int)RTSNavigationLib::TriangleInterfacePoint::BottomCenter);
    spike3->setParentInterfacePoint(27);
    spike3->setRotation(glm::pi<double>() * 0.5);

    std::unique_ptr<RTSNavigationLib::Formation> spike4 = std::make_unique<RTSNavigationLib::Formation>();
    spike4->setShape(std::make_unique<RTSNavigationLib::TriangleFormationShape>());
    spike4->setUnitCategories({ 2 });
    spike4->setOwnInterfacePoint((int)RTSNavigationLib::TriangleInterfacePoint::BottomCenter);
    spike4->setParentInterfacePoint(18);
    spike4->setRotation(glm::pi<double>());

    std::unique_ptr<RTSNavigationLib::Formation> formation2 = std::make_unique<RTSNavigationLib::Formation>();
    formation2->addChild(std::move(spike));
    formation2->addChild(std::move(spike2));
    formation2->addChild(std::move(spike3));
    formation2->addChild(std::move(spike4));
    formation2->setShape(std::make_unique<RTSNavigationLib::ArcFormationShape>());
    formation2->setUnitCategories({ 1 });
    formation.addChild(std::move(formation2));

    auto places = RTSNavigationLib::FormationCalculator(formation, input).calculate();

    REQUIRE(places.size() == input.size());

    auto categories = countCategories(places);
    REQUIRE(categories[0] == 350);
    REQUIRE(categories[1] == 700);
    REQUIRE(categories[2] == 500);
  }
}