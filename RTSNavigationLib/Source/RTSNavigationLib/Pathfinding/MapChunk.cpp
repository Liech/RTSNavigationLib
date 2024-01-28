#include "MapChunk.h"

#include <stdexcept>

#include "EikonalGrid.h"
#include "DijkstraGrid.h"
#include "FlowField.h"

namespace RTSNavigationLib {
  MapChunk::MapChunk(const std::vector<float>& obstacles_, const glm::ivec2& resolution_, bool eikonal_) {
    resolution = resolution_;
    eikonal = eikonal_;
    obstacles = obstacles_;

    portals.resize(4);
    initializePortals(MajorDirection2D::Top  , glm::ivec2(0, 0), glm::ivec2(resolution.x - 1, 0));
    initializePortals(MajorDirection2D::Bot  , glm::ivec2(0, resolution.y-1), glm::ivec2(resolution.x - 1, resolution.y - 1));
    initializePortals(MajorDirection2D::Left , glm::ivec2(0, 0), glm::ivec2(0, resolution.y - 1));
    initializePortals(MajorDirection2D::Right, glm::ivec2(resolution.x - 1, 0), glm::ivec2(resolution.x - 1, resolution.y - 1));
  }

  unsigned char MapChunk::numberPortals(MajorDirection2D dir)  const {
    return portals[(int)dir].size();
  }
  
  float MapChunk::getTraverseCost(MajorDirection2D startDir, unsigned char startPortalId, MajorDirection2D endDir, unsigned char endPortalId) const {
    throw std::runtime_error("Not implemented Yet");
  }

  const FlowField& MapChunk::getMap(MajorDirection2D dir, unsigned char portalId) {
    auto id = std::make_pair(dir, portalId);
    if (navigationMaps.count(id) == 0)
      calculateMap(dir, portalId);
    return navigationMaps.at(id);
  }

  glm::ivec2 MapChunk::getResolution() const {
    return resolution;
  }

  const std::vector<float>& MapChunk::getObstacles() const {
    return obstacles;
  }

  bool MapChunk::getEikonal() const {
    return eikonal;
  }

  void MapChunk::calculateMap(MajorDirection2D dir, unsigned char portalID) {
    const auto& portal = portals[(int)dir][portalID];
    const glm::ivec2& from = portal.first;
    const glm::ivec2& to = portal.second;
    size_t distance = (to.x - from.x) + (to.y - from.y) + 1;
    glm::ivec2 increment = glm::ivec2((to.x - from.x) > 0 ? 1 : 0, (to.y - from.y) > 0 ? 1 : 0);

    std::vector<glm::ivec2> targets;
    glm::ivec2 current = from;
    for (size_t i = 0; i < distance; i++) {
      targets.push_back(current);
      current += increment;
    }
    auto id = std::make_pair(dir, portalID);
    if (eikonal) {
      RTSNavigationLib::EikonalGrid grid(obstacles, resolution, targets);
      navigationMaps.emplace(std::make_pair(id,RTSNavigationLib::FlowField(grid)));
    }
    else {
      RTSNavigationLib::DijkstraGrid grid(obstacles, resolution, targets);
      navigationMaps.emplace(std::make_pair(id, RTSNavigationLib::FlowField(grid)));
    }
  }

  void MapChunk::initializePortals(MajorDirection2D dir, const glm::ivec2& from, const glm::ivec2& to) {
    size_t distance = (to.x - from.x) + (to.y - from.y) + 1;
    glm::ivec2 increment = glm::ivec2((to.x - from.x) > 0 ? 1 : 0, (to.y - from.y) > 0 ? 1 : 0);
    constexpr float infinity = std::numeric_limits<float>::infinity();
    auto isBlocked = [this, infinity](const glm::ivec2& v) { return obstacles[v.x + v.y * resolution.x] == infinity; };

    glm::ivec2 portalStart = from;
    glm::ivec2 current     = from;
    bool active = !isBlocked(current);
    for (size_t i = 0; i < distance; i++) {
      bool blocked = isBlocked(current);
      if (active && blocked) {
        portals[(int)dir].push_back(std::make_pair(portalStart, current - increment));
        active = false;
      }
      else if (!active && !blocked) {
        active = true;
        portalStart = current;
      }

      current += increment;
    }
    if (active) {
      portals[(int)dir].push_back(std::make_pair(portalStart, current - increment));
    }
  }

}