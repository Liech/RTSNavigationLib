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
    static std::vector<Body>                          formate(std::map<size_t, std::map<size_t, size_t>>& current, const std::map<size_t, std::map<size_t, size_t>>& overall, glm::mat4& transformation, const Formation&, bool& bigEnough);
    static RectangleGrid<bool>                        getGrid(const Formation&, const glm::mat4& transformation);
    static std::vector<Body>                          placeUnits(const RectangleGrid<bool>&, const std::map<size_t, size_t>&, const glm::vec2& offset, size_t category, bool& allPlaced);
    static std::pair<glm::vec2, glm::vec2>            getMinMax(const std::vector<glm::vec2>&);
    static glm::mat4                                  getLocalTransformation(const Formation&, size_t scale);
    static size_t                                     getSizeSum(const std::map<size_t, size_t>&);
    static std::map<size_t, size_t>                   gatherUnits(const Formation&, const std::map<size_t, std::map<size_t, size_t>>& OverallUnits, std::map<size_t, std::map<size_t, size_t>>& availableUnits);
    static std::map<size_t, std::map<size_t, size_t>> getSizesPerCategory(const std::vector<Body>& units);
    static std::map<size_t, float>                    getCategoryWeightSum(const Formation&);
  };
}