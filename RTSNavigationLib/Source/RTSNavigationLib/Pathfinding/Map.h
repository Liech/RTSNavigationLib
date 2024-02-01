#pragma once

#include <vector>
#include <memory>
#include <glm/glm.hpp>

namespace RTSNavigationLib {
  class FlowField;
  class MapChunk;

  struct MapGuide{
    glm::ivec2 offset;
    std::weak_ptr<const FlowField> flowField;
  };
  

  class Map {
  public:
    Map(const std::vector<float>& obstacles,const glm::ivec2 resolution, const glm::ivec2& subResolution, bool eikonal = true);
    virtual ~Map();

    //rough estimate how to move, instantly ready, when moved to border of a flow field or pointer dead request new one
    MapGuide getMap(const glm::ivec2& from, const glm::ivec2& to) const;

    ////minimal mask where pathfinding calculations on obstacles array are necessary to get best result
    //std::vector<bool> getCalculationMask(const std::vector<glm::ivec2>& froms, const glm::ivec2& to) const;

    size_t addCostStamp(const std::vector<float>& obstacles, const glm::ivec2 resolution);
    void   removeCostStamp(size_t);

    glm::ivec2 getResolution()    const;
    glm::ivec2 getSubResolution() const;
    bool       getEikonal()       const;

  private:
    void initChunks();

    glm::ivec2         resolution;
    glm::ivec2         subResolution;
    std::vector<float> obstacles;
    bool               eikonal;
    const size_t       overlap = 1;
    
    glm::ivec2 amountChunks;
    std::vector<std::unique_ptr<MapChunk>> chunks;
    std::vector<glm::ivec2>                offsets;
  };
}