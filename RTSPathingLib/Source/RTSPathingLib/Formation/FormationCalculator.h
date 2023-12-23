#pragma once

#include <map>
#include <vector>
#include <glm/glm.hpp>

#include "RTSPathingLib/Util/RectangleGrid/RectangleGrid.h"

namespace RTSPathingLib {
  struct Body;
  class Formation;

  class FormationCalculator {
  public:
    static std::vector<Body> calculate(const Formation&, const std::vector<Body>& units);

  private:
    static std::vector<Body>                          formate(std::map<size_t, std::map<size_t, size_t>>& current, const std::map<size_t, std::map<size_t, size_t>>& overall, const glm::dvec2& startPoint, const Formation&, std::vector<RectangleGrid<bool>>& allGrids);
    static void                                       saveAsSvg(const std::vector<Body>& bodies, std::vector<RectangleGrid<bool>>& allGrids, const RectangleGrid<bool>& grid, const std::vector<glm::dvec2>& currentPolygon);
    static glm::dvec3                                 getScalingVector(const Formation&, size_t scale);
    static RectangleGrid<bool>                        getGrid(const Formation&, const glm::dmat4& transformation, std::vector<glm::dvec2>& polygon, const std::vector<RectangleGrid<bool>>& allGrids);
    static std::vector<Body>                          placeUnits(RectangleGrid<bool>&, const std::map<size_t, size_t>&, const glm::dvec2& offset, size_t category, bool& allPlaced);
    static std::pair<glm::dvec2, glm::dvec2>          getMinMax(const std::vector<glm::dvec2>&);
    static glm::dmat4                                 getLocalTransformation(const Formation&, const glm::dvec2& startPoint, size_t scale);
    static size_t                                     getSizeSum(const std::map<size_t, size_t>&);
    static std::map<size_t, size_t>                   gatherUnits(const Formation&, const std::map<size_t, std::map<size_t, size_t>>& OverallUnits, std::map<size_t, std::map<size_t, size_t>>& availableUnits);
    static std::map<size_t, std::map<size_t, size_t>> getSizesPerCategory(const std::vector<Body>& units);
    static std::map<size_t, double>                   getCategoryWeightSum(const Formation&);
  };
}