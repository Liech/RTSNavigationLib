#include "Portal.h"

namespace RTSNavigationLib {
  Portal::Portal(const std::vector<float>& obstacles_, const glm::ivec2& resolution_) :
    obstacles(obstacles_),
    resolution(resolution_)
  {
    
  }
}