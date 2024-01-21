#pragma once

#include <vector>
#include <glm/glm.hpp>

namespace RTSPathingLib {
  class FlowField {
  public:
    FlowField(const std::vector<float>& obstacles, const glm::ivec2& resolution, const glm::ivec2& target);

    glm::dvec2 getDirection(const glm::ivec2& location) const;
  private:
    void initField(const std::vector<float>& obstacles);

    glm::ivec2             resolution;
    glm::ivec2             target;
    std::vector<glm::vec2> field;
  };
}