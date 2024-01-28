#pragma once

#include <vector>
#include <memory>
#include <glm/glm.hpp>


namespace RTSNavigationLib {
  class FlowField;
  class MapChunk;

  class Map {
  public:
    Map(const std::vector<float>& obstacles,const glm::ivec2 resolution, const glm::ivec2& subResolution, size_t overlap, bool eikonal = true);
    virtual ~Map();

          size_t     getMap(const glm::ivec2& from, const glm::ivec2& to);    
          float      getDistance(const glm::ivec2& from, const glm::ivec2& to);
          bool       hasMap(size_t id) const;
    const FlowField& getMap(size_t id) const;
    glm::ivec2 getOffset(size_t id) const;

    size_t addCostStamp(const std::vector<float>& obstacles, const glm::ivec2 resolution);
    void   removeCostStamp(size_t);

    glm::ivec2 getResolution()    const;
    glm::ivec2 getSubResolution() const;
    bool       getEikonal()       const;
    size_t     getOverlap()       const;

  private:
    void initChunks();

    glm::ivec2         resolution;
    glm::ivec2         subResolution;
    std::vector<float> obstacles;
    bool               eikonal;
    size_t             overlap;
    
    glm::ivec2 amountChunks;
    std::vector<std::unique_ptr<MapChunk>> chunks;
    std::vector<glm::ivec2>                offsets;
  };
}