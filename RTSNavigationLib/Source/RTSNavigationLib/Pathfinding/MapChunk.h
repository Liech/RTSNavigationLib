#pragma once

#include <vector>
#include <tuple>
#include <glm/glm.hpp>
#include <map>
#include <memory>

#include "RTSNavigationLib/MajorDirection2D.h"
#include "RTSNavigationLib/Pathfinding/FlowField.h"

namespace RTSNavigationLib {
  class MapChunk {
  public:
    MapChunk(const std::vector<float>& obstacles, const glm::ivec2& resolution, bool eikonal = true);

    unsigned char numberPortals(MajorDirection2D)  const;
    float getTraverseCost(MajorDirection2D startDir, unsigned char startPortalId, MajorDirection2D endDir, unsigned char endPortalId);
    std::weak_ptr<const FlowField> getMap(MajorDirection2D dir, unsigned char portalId);
    void precalculateEverything();

    glm::ivec2 getResolution() const;
    const std::vector<float>& getObstacles() const;
    bool getEikonal() const;

  private:
    void initializePortals(MajorDirection2D dir, const glm::ivec2& from, const glm::ivec2& to);
    void calculateMap(MajorDirection2D, unsigned char);
    void calculateCost(const std::pair<std::pair<MajorDirection2D, unsigned char>, std::pair<MajorDirection2D, unsigned char>>& id);

    glm::ivec2 resolution;
    bool eikonal;
    std::vector<float> obstacles;

    std::vector<std::vector<std::pair<glm::ivec2, glm::ivec2>>> portals;
    std::map<std::pair<MajorDirection2D, unsigned char>, std::shared_ptr<FlowField>> navigationMaps;
    std::map<std::pair<std::pair<MajorDirection2D, unsigned char>, std::pair<MajorDirection2D, unsigned char>>, float> traverseCost;
  };
}