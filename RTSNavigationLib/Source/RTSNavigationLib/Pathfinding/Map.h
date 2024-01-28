#pragma once

#include <vector>
#include <glm/glm.hpp>

namespace RTSNavigationLib {
  class FlowField;

  class Map {
  public:
    Map(const std::vector<float>& obstacles,const glm::ivec2 resolution, const glm::ivec2& subResolution, bool eikonal = true);

          size_t     getMap(const glm::ivec2& from, const glm::ivec2& to);    
          float      getDistance(const glm::ivec2& from, const glm::ivec2& to);
          bool       hasMap(size_t id) const;
    const FlowField& getMap(size_t id) const;

    size_t addCostStamp(const std::vector<float>& obstacles, const glm::ivec2 resolution);
    void   removeCostStamp(size_t);

  private:
    glm::ivec2         resolution;
    glm::ivec2         subResolution;
    std::vector<float> obstacles;
    bool               eikonal;
    
  };
}