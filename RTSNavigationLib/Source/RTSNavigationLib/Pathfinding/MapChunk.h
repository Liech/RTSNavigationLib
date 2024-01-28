#pragma once

#include <vector>
#include <tuple>
#include <glm/glm.hpp>
#include <map>

#include "RTSNavigationLib/MajorDirection2D.h"
#include "RTSNavigationLib/Pathfinding/FlowField.h"

namespace RTSNavigationLib {
  class MapChunk {
  public:
    MapChunk(const std::vector<float>& obstacles, const glm::ivec2& resolution, bool eikonal = true);

    size_t numberPortals(MajorDirection2D)  const;
    float getTraverseCost(MajorDirection2D startDir, unsigned char startPortalId, MajorDirection2D endDir, unsigned char endPortalId) const;
    const FlowField& getMap(MajorDirection2D startDir, unsigned char startPortalId, MajorDirection2D endDir, unsigned char endPortalId);
    glm::ivec2 getResolution() const;

  private:
    glm::ivec2 resolution;
    bool eikonal;
    std::vector<float> obstacles;

    std::map<std::tuple<MajorDirection2D, unsigned char, MajorDirection2D, unsigned char>, FlowField> navigationMaps;
  };
}