#include "TriangleFormationShape.h"

#include <glm/ext/scalar_constants.hpp>

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

glm::vec2 TriangleFormationShape::getInterfacePoint(size_t number) const {
  if (number == 0)
    return glm::vec2(0, 0);
  size_t edge = ((number - 1) / 2) % 3;
  bool center = (number - 1) % 2 == 0;
  auto poly = getPolygon();
  glm::vec2 result = poly[edge];
  if (center)
    result += (poly[(edge + 1) % 3] - poly[edge]) / 2.0f;
  return result;
}

std::vector<glm::vec2> TriangleFormationShape::getPolygon() const {
  glm::vec2 size = getBaseSize();
  return std::vector<glm::vec2>{
    glm::vec2(size.x * std::cos(0)                              , size.y * std::sin(0)),
    glm::vec2(size.x * std::cos((glm::pi<float>() * 2.0f)/3)    , size.y * std::sin((glm::pi<float>() * 2.0f) / 3)),
    glm::vec2(size.x * std::cos(2*(glm::pi<float>() * 2.0f) / 3), size.y * std::sin(2*(glm::pi<float>() * 2.0f) / 3)),
  };
}

float TriangleFormationShape::getInterfaceWidth(size_t number) const {
  if (number == 0)
    return 0;
  size_t edge = ((number - 1) / 2) % 3;
  bool center = (number - 1) % 2 == 0;
  if (!center)
    return 0;
  auto poly = getPolygon();
  float result = glm::distance(poly[edge], poly[(edge + 1) % 3]);
  return result;
}

glm::vec2 TriangleFormationShape::getInterfaceNormal(size_t number) const {
  if (number == 0)
    return glm::vec2(0, 1);
  size_t edge = (number - 1) % 3;
  bool center = (number - 1) % 2 == 0;
  if (!center)
    return glm::vec2(0, 1);
  auto poly = getPolygon();
  glm::vec2 result = glm::normalize(poly[(edge + 1) % 3] - poly[edge]);
  result = glm::vec2(-result.y, result.x);
  if (glm::length(result) < 1e-5)
    return glm::vec2(0, 1);
  return result;
}