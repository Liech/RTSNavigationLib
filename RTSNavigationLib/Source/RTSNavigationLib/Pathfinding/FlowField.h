#pragma once

#include <vector>
#include <glm/glm.hpp>

namespace RTSPathingLib {
  class FlowField {
  public:
    FlowField(const std::vector<bool>& obstacles, const glm::ivec2& resolution);

    void       setTarget   (const glm::ivec2& target);
    glm::dvec2 getDirection(const glm::ivec2& location) const;
  private:

  };
}