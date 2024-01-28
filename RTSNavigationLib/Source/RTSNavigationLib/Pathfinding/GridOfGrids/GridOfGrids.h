#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "PortalNode.h"

namespace RTSNavigationLib {
  class GridOfGrids {
  public:
    GridOfGrids(const std::vector<float>& obstacles, const glm::ivec2& resolution, const glm::ivec2& subResolution, size_t overlap = 2);


  private:
    void initUnawarePortals(); //obstacle unaware portals asuming plain field, dividing later

    std::vector<float> obstacles;
    glm::ivec2         resolution;
    glm::ivec2         subResolution;
    size_t             overlap;

    glm::ivec2 gridSize;

    std::vector<PortalNode> portals;
  };
}