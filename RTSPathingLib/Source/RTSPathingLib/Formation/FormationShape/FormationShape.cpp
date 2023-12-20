#include "FormationShape.h"

FormationShape::FormationShape() {

}

FormationShape::~FormationShape() {

}

std::string FormationShape::getType() const {
  return "Base";
}

size_t FormationShape::getNumberOfInterfacePoints() const {
  return 1;
}

glm::vec2 FormationShape::getInterfacePoint(size_t number) const {
  return glm::vec2(0, 0);
}

glm::vec2 FormationShape::getInterfaceNormal(size_t number) const {
  return glm::vec2(0, 1);
}

std::vector<glm::vec2> FormationShape::getPolygon() const {
  return {};
}

float FormationShape::getInterfaceWidth(size_t) const {
  return 0;
}

ScalingBehavior FormationShape::getScalingBehavior() const {
  return scaling;
}

void FormationShape::setScalingBehavior(const ScalingBehavior& behavior) {
  scaling = behavior;
}

glm::vec2 FormationShape::getBaseSize() const {
  return baseSize;
}

void FormationShape::setBaseSize(const glm::vec2& size) {
  baseSize = size;
}
