#include "FlowField.h"

namespace RTSPathingLib {
  FlowField::FlowField(const std::vector<bool>& obstacles, const glm::ivec2& resolution) {

  }

  void FlowField::setTarget(const glm::ivec2& target) {

  }

  glm::dvec2 FlowField::getDirection(const glm::ivec2& location) const {
    return glm::dvec2(0, 0);
  }
}