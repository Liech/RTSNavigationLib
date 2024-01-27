#pragma once

#include <vector>
#include <glm/glm.hpp>

namespace RTSNavigationLib {
  class Portal {
  public:
    Portal(const std::vector<float>& obstacles, const glm::ivec2& resolution);


  private:
    std::vector<float> obstacles;
    glm::ivec2         resolution;


  };
}