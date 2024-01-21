#include "RectangleFormationShape.h"

namespace RTSNavigationLib {
  RectangleFormationShape::RectangleFormationShape() {

  }

  RectangleFormationShape::~RectangleFormationShape() {

  }

  std::string RectangleFormationShape::getType() const {
    return "Rectangle";
  }

  size_t RectangleFormationShape::getNumberOfInterfacePoints() const {
    return 9;
  }

  glm::dvec2 RectangleFormationShape::getInterfacePoint(size_t number) const {
    if (number == 0)
      return glm::dvec2(0, 0);
    size_t edge = ((number - 1) / 2) % 4;
    bool center = (number - 1) % 2 == 1;
    auto poly = getPolygon();
    glm::dvec2 result = poly[edge];
    if (center)
      result += (poly[(edge + 1) % 4] - poly[edge]) / 2.0;
    return result;
  }

  std::vector<glm::dvec2> RectangleFormationShape::getPolygon() const {
    glm::dvec2 size = getBaseSize();
    return {
      glm::dvec2(-0.5 * size.x,-0.5 * size.y),
      glm::dvec2(0.5 * size.x,-0.5 * size.y) ,
      glm::dvec2(0.5 * size.x, 0.5 * size.y) ,
      glm::dvec2(-0.5 * size.x, 0.5 * size.y),
    };
  }

  double RectangleFormationShape::getInterfaceWidth(size_t number, const glm::dvec2& scale) const {
    if (number == 0)
      return 0;
    size_t edge = ((number - 1) / 2) % 4;
    bool center = (number - 1) % 2 == 1;
    if (!center)
      return 0;
    auto poly = getPolygon();
    double result = glm::distance(poly[edge]*scale, poly[(edge + 1) % 4]*scale);
    return result;
  }

  glm::dvec2 RectangleFormationShape::getInterfaceNormal(size_t number) const {
    if (number == 0)
      return glm::dvec2(0, 1);
    size_t edge = (number - 1) % 4;
    bool center = (number - 1) % 2 == 1;
    if (!center)
      return glm::dvec2(0, 1);
    auto poly = getPolygon();
    glm::dvec2 result = glm::normalize(poly[(edge + 1) % 4] - poly[edge]);
    result = glm::dvec2(-result.y, result.x);
    if (glm::length(result) < 1e-5)
      return glm::dvec2(0, 1);
    return result;
  }

  void RectangleFormationShape::fromJson(const nlohmann::json& input) {
    FormationShape::fromJson(input);    
  }

  nlohmann::json RectangleFormationShape::toJson() {
    nlohmann::json result = FormationShape::toJson();
    result["Type"] = "Rectangle";
    return result;
  }
}