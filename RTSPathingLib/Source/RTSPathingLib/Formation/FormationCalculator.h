#pragma once

#include <map>
#include <vector>
#include <glm/glm.hpp>


namespace RTSPathingLib {
  struct Body;
  class Formation;
  class RectangleGrid;

  class FormationCalculator {
  public:
    static std::vector<Body> calculate(const Formation&, const std::vector<Body>& units);

  private:
    static size_t getSizeSum(const std::map<size_t, size_t>&);
    static std::map<size_t, size_t> gatherUnits(const Formation&, const std::map<size_t, std::map<size_t, size_t>>& OverallUnits, std::map<size_t, std::map<size_t, size_t>>& availableUnits);
    static std::map<size_t, std::map<size_t, size_t>> getSizesPerCategory(const std::vector<Body>& units);
    static std::map<size_t, float> getCategoryWeightSum(const Formation&);
  };
}