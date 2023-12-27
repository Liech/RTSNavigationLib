#include "TriangleFormationShape.h"

#include <glm/ext/scalar_constants.hpp>

namespace RTSPathingLib {
  TriangleFormationShape::TriangleFormationShape() {

  }

  TriangleFormationShape::~TriangleFormationShape() {

  }

  std::string TriangleFormationShape::getType() const {
    return "Triangle";
  }

  size_t TriangleFormationShape::getNumberOfInterfacePoints() const {
    return 7;
  }

  glm::dvec2 TriangleFormationShape::getInterfacePoint(size_t number) const {
    if (number == 0)
      return glm::dvec2(0, 0);
    size_t edge = ((number - 1) / 2) % 3;
    bool center = (number - 1) % 2 == 1;
    auto poly = getPolygon();
    glm::dvec2 result = poly[edge];
    if (center)
      result += (poly[(edge + 1) % 3] - poly[edge]) / 2.0;
    return result;
  }

  std::vector<glm::dvec2> TriangleFormationShape::getPolygon() const {
    glm::dvec2 size = getBaseSize() ;
    return std::vector<glm::dvec2>{
      glm::dvec2(size.x * -0.5, size.y * -0.5),
      glm::dvec2(size.x *  0.0, size.y * 0.5),
      glm::dvec2(size.x *  0.5, size.y * -0.5),
    };
  }

  double TriangleFormationShape::getInterfaceWidth(size_t number, const glm::dvec2& scale) const {
    if (number == 0)
      return 0;
    size_t edge = ((number - 1) / 2) % 3;
    bool center = (number - 1) % 2 == 1;
    if (!center)
      return 0;
    auto poly = getPolygon();
    double result = glm::distance(poly[edge]*scale, poly[(edge + 1) % 3]*scale);
    return result;
  }

  glm::dvec2 TriangleFormationShape::getInterfaceNormal(size_t number) const {
    if (number == 0)
      return glm::dvec2(0, 1);
    size_t edge = (number - 1) % 3;
    bool center = (number - 1) % 2 == 1;
    if (!center)
      return glm::dvec2(0, 1);
    auto poly = getPolygon();
    glm::dvec2 result = glm::normalize(poly[(edge + 1) % 3] - poly[edge]);
    result = glm::dvec2(-result.y, result.x);
    if (glm::length(result) < 1e-5)
      return glm::dvec2(0, 1);
    return result;
  }
}