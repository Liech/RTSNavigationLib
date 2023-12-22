#include "FormationShape.h"

namespace RTSPathingLib {
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

  glm::dvec2 FormationShape::getInterfacePoint(size_t number) const {
    return glm::dvec2(0, 0);
  }

  glm::dvec2 FormationShape::getInterfaceNormal(size_t number) const {
    return glm::dvec2(0, 1);
  }

  std::vector<glm::dvec2> FormationShape::getPolygon() const {
    return {};
  }

  double FormationShape::getInterfaceWidth(size_t) const {
    return 0;
  }

  ScalingBehavior FormationShape::getScalingBehavior() const {
    return scaling;
  }

  void FormationShape::setScalingBehavior(const ScalingBehavior& behavior) {
    scaling = behavior;
  }

  glm::dvec2 FormationShape::getBaseSize() const {
    return baseSize;
  }

  void FormationShape::setBaseSize(const glm::dvec2& size) {
    baseSize = size;
  }
}