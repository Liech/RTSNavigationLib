#include "MapChunk.h"

#include <stdexcept>

namespace RTSNavigationLib {
  MapChunk::MapChunk(const std::vector<float>& obstacles_, const glm::ivec2& resolution_, bool eikonal_) {
    resolution = resolution_;
    eikonal = eikonal_;
    obstacles = obstacles_;

    throw std::runtime_error("Not implemented Yet");
  }

  size_t MapChunk::numberPortals(MajorDirection2D)  const {
    throw std::runtime_error("Not implemented Yet");
  }
  
  float MapChunk::getTraverseCost(MajorDirection2D startDir, unsigned char startPortalId, MajorDirection2D endDir, unsigned char endPortalId) const {
    throw std::runtime_error("Not implemented Yet");
  }

  const FlowField& MapChunk::getMap(MajorDirection2D startDir, unsigned char startPortalId, MajorDirection2D endDir, unsigned char endPortalId) {
    throw std::runtime_error("Not implemented Yet");
  }

  glm::ivec2 MapChunk::getResolution() const {
    return resolution;
  }
}