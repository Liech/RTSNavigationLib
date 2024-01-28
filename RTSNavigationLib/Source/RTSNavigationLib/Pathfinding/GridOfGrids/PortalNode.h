#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace RTSNavigationLib {
  class PortalNode {
  public:
    glm::ivec2 start;
    glm::ivec2 end;

    size_t gridA;
    size_t gridB;
    std::vector<size_t> PortalsToA;
    std::vector<size_t> PortalsToB;
  private:
  };
}