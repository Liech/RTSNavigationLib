#include "FormationShape.h"

FormationShape::FormationShape() {

}

FormationShape::~FormationShape() {

}

std::vector<glm::vec2> FormationShape::getPolygon() const {
  return {};
}

float FormationShape::getAngle() const {
  return angle;
}

void FormationShape::setAngle(float angle_) {
  angle = angle_;
}

float FormationShape::getInterfaceWidth() const {
  return 0;
}

void FormationShape::setLayoutCentered(bool v) {
  layoutCentered = v;
}

bool FormationShape::getLayoutCentered() const {
  return layoutCentered;
}