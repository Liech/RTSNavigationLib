#include "ArcFormationShape.h"

#include <glm/ext/scalar_constants.hpp>

ArcFormationShape::ArcFormationShape() {

}

ArcFormationShape::~ArcFormationShape() {

}

std::string ArcFormationShape::getType() const {
  return "Arc";
}

size_t ArcFormationShape::getNumberOfInterfacePoints() const {
  return numberPolygons+1;
}

glm::vec2 ArcFormationShape::getInterfacePoint(size_t number) const {
  if (number == 0)
    return glm::vec2(0, 0);
  size_t edge = (number - 1) % numberPolygons;
  auto poly = getPolygon();
  glm::vec2 result = poly[edge] + (poly[(edge + 1) % numberPolygons] - poly[edge]) / 2.0f;
  return result;
}

std::vector<glm::vec2> ArcFormationShape::getPolygon() const {
  std::vector<glm::vec2> result;
  glm::vec2 size = getBaseSize();

  float from = arcAngleRadian / 2;
  float till = glm::pi<float>() * 2 - from;
  
  for (size_t i = 0; i < numberPolygons; i++) {
    float perc = (float)i / (float)numberPolygons;
    float angle = from + (till - from) * perc;    
    glm::vec2 pos = glm::vec2(std::cos(angle)*size.x*0.5f, std::sin(angle) * size.y*0.5f);
    result.push_back(pos);
  }
  if (arcAngleRadian != 0)
    result.push_back(glm::vec2(0, 0));

  return result;
}

float ArcFormationShape::getInterfaceWidth(size_t number) const {
  if (number == 0)
    return 0;
  size_t edge = (number - 1) % numberPolygons;
  auto poly = getPolygon();
  float result = glm::distance(poly[edge],poly[(edge + 1) % numberPolygons]);
  return result;
}

float ArcFormationShape::getArcAngle() const {
  return arcAngleRadian;
}

void ArcFormationShape::setArcAngle(float valueRadian) {
  arcAngleRadian = valueRadian;
}

glm::vec2 ArcFormationShape::getInterfaceNormal(size_t number) const {
  if (number == 0)
    return glm::vec2(0, 1);
  size_t edge = (number - 1) % numberPolygons;
  auto poly = getPolygon();
  glm::vec2 result = glm::normalize(poly[(edge + 1) % numberPolygons] - poly[edge]);
  result = glm::vec2(-result.y, result.x);
  if (glm::length(result) < 1e-5)
    return glm::vec2(0, 1);
  return result;
}
