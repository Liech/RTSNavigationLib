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
  
  float MapChunk::getTraverseCost(MajorDirection2D startDir, unsigned char startPortalId, MajorDirection2D endDir, unsigned char endPortalId) {
    auto id = std::make_pair(std::make_pair(startDir, startPortalId), std::make_pair(endDir, endPortalId));
    if (traverseCost.count(id) == 0)
      calculateCost(id);
    return traverseCost.at(id);
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

  void MapChunk::calculateCost(const std::pair<std::pair<MajorDirection2D, unsigned char>, std::pair<MajorDirection2D, unsigned char>>& id) {
    const auto& targetID = id.second;
    const auto& startID = id.first;
    if (navigationMaps.count(targetID) == 0)
      calculateMap(targetID.first, targetID.second);
    const auto& map = navigationMaps.at(targetID);
    const auto& portal = portals[(int)startID.first][startID.second];
    glm::ivec2 start = (portal.first + portal.second) / 2;

    glm::dvec2 current = (glm::dvec2)start + glm::dvec2(0.5,0.5);
    double distance = 0;
    while (true) {
      auto dir = map.getDirection(current);
      if (dir.x+dir.y == 0)
        break;
      current += dir;
      distance += 1;
    }
    traverseCost[id] = distance;
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

  void MapChunk::precalculateEverything() {
    for (int dir = 0; dir < 4; dir++) {
      auto d = (MajorDirection2D)dir;
      size_t amountPortals = numberPortals(d);
      for (size_t portalID = 0; portalID < amountPortals; portalID++) {
        auto id = std::make_pair(d, portalID);
        if (navigationMaps.count(id) == 0)
          calculateMap(d, portalID);

        for (int targetDir = 0; targetDir < 4; targetDir++) {
          auto d2 = (MajorDirection2D)targetDir;
          size_t amountPortals = numberPortals(d2);
          for (size_t portalID2 = 0; portalID2 < amountPortals; portalID2++) {
            auto id2 = std::make_pair(d2, portalID2);
            auto costID = std::make_pair(id, id2);
            if (traverseCost.count(costID) == 0 && id != id2)
              calculateCost(costID);
          }
        }
      }
    }
  }
}