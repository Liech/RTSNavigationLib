#include "Map.h"

#include <stdexcept>

#include "RTSNavigationLib/Pathfinding/MapChunk.h"

namespace RTSNavigationLib {
  Map::Map(const std::vector<float>& obstacles_, const glm::ivec2 resolution_, const glm::ivec2& subResolution_, bool eikonal_) {
    resolution    = resolution_;
    subResolution = subResolution_;
    obstacles     = obstacles_;
    eikonal       = eikonal_;

    initChunks();
  }

  Map::~Map() {

  }

  MapGuide Map::getMap(const glm::ivec2& from, const glm::ivec2& to) const {

  }

  //float Map::getDistance(const glm::ivec2& from, const glm::ivec2& to) {
  //  throw std::runtime_error("Not implemented Yet!");
  //}

  size_t Map::addCostStamp(const std::vector<float>& obstacles, const glm::ivec2 resolution) {
    throw std::runtime_error("Not implemented Yet!");
  }

  void Map::removeCostStamp(size_t) {
    throw std::runtime_error("Not implemented Yet!");
  }

  glm::ivec2 Map::getResolution() const {
    return resolution;
  }

  glm::ivec2 Map::getSubResolution() const {
    return subResolution;
  }

  bool Map::getEikonal() const {
    return eikonal;
  }

  void Map::initChunks() {
    amountChunks = glm::ivec2(std::ceil(resolution.x / subResolution.x), std::ceil(resolution.x / subResolution.x));
    chunks.resize(amountChunks.x * amountChunks.y);
    offsets.resize(amountChunks.x * amountChunks.y);

    glm::ivec2 chunkResolution = subResolution + glm::ivec2(overlap,overlap) * 2;
#pragma omp parallel for
    for (long long cell = 0; cell < chunks.size(); cell++) {
      std::vector<float> localObstacles;
      localObstacles.resize(chunkResolution.x * chunkResolution.y, std::numeric_limits<float>::infinity());
      glm::ivec2 offset = glm::ivec2((cell % amountChunks.x)*chunkResolution.x - overlap, (cell / amountChunks.x)*chunkResolution.y - overlap);

      for (size_t x = 0; x < chunkResolution.x; x++)
        for (size_t y = 0; y < chunkResolution.y; y++) {
          glm::ivec2 o = glm::ivec2(x, y) + offset;
          if (o.x < 0 || o.x >= resolution.x || o.y < 0 || o.y >= resolution.y)
            continue;
          localObstacles[x + y * chunkResolution.x] = obstacles[o.x+o.y*resolution.x];
        }
      chunks[cell] = std::make_unique<MapChunk>(localObstacles, chunkResolution, eikonal);
      offsets[cell] = offset;
    }
  }
}