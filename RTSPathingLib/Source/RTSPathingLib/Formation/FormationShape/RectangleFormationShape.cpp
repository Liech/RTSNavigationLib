#include "RectangleFormationShape.h"

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

glm::vec2 RectangleFormationShape::getInterfacePoint(size_t number) const {
  if (number == 0)
    return glm::vec2(0, 0);
  size_t edge = ((number - 1) / 2)%4;
  bool center = (number - 1) % 2 == 0;
  auto poly = getPolygon();
  glm::vec2 result = poly[edge];
  if (center)
    result += (poly[(edge+1)%4] - poly[edge]) / 2.0f;
  return result;
}

std::vector<glm::vec2> RectangleFormationShape::getPolygon() const {
  glm::vec2 size = getBaseSize();
  return {
    glm::vec2(-0.5f*size.x,-0.5f*size.y),
    glm::vec2( 0.5f*size.x,-0.5f*size.y),
    glm::vec2( 0.5f*size.x, 0.5f*size.y),
    glm::vec2(-0.5f*size.x, 0.5f*size.y),
  };
}

float RectangleFormationShape::getInterfaceWidth(size_t number) const {
  if (number == 0)
    return 0;
  size_t edge = ((number - 1) / 2) % 4;
  bool center = (number - 1) % 2 == 0;
  if (!center)
    return 0;
  auto poly = getPolygon();
  float result = glm::distance(poly[edge], poly[(edge + 1) % 4]);
  return result;
}