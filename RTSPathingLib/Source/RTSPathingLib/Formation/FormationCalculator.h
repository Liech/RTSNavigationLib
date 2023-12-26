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
    FormationCalculator(const Formation&, const std::vector<Body>& units);

    std::vector<Body> calculate();

  private:
    const Formation&         rootFormation;
    const std::vector<Body>& inputUnits;

    std::map<size_t, std::map<size_t, size_t>> overall;
    std::map<size_t, std::map<size_t, size_t>> currentUnits;
    std::vector<RectangleGrid<bool>> allGrids;
    std::vector<glm::dvec2> lastpolygon;
    std::map<size_t, double> weightSumPerCategory;

    bool saveSVG = false;

    std::vector<Body>                          recurse( const glm::dvec2& parentCenter, size_t parentSize, const Formation&);
    void                                       saveAsSvg(const std::vector<Body>& bodies, const RectangleGrid<bool>& grid, const std::vector<glm::dvec2>& currentPolygon);
    glm::dvec3                                 getScalingVector(const Formation&, size_t scale);
    RectangleGrid<bool>                        getGrid(const Formation&, const glm::dmat4& transformation, std::vector<glm::dvec2>& polygon);
    std::vector<Body>                          placeUnits(RectangleGrid<bool>&, const std::map<size_t, size_t>&, const glm::dvec2& offset, size_t category, bool& allPlaced);
    std::pair<glm::dvec2, glm::dvec2>          getMinMax(const std::vector<glm::dvec2>&);
    glm::dmat4                                 getLocalTransformation(const Formation&, const glm::dvec2& parentCenter, size_t parentScale, size_t scale);
    size_t                                     getSizeSum(const std::map<size_t, size_t>&);
    std::map<size_t, size_t>                   gatherUnits(const Formation&);
    std::map<size_t, std::map<size_t, size_t>> getSizesPerCategory(const std::vector<Body>& units);
    std::map<size_t, double>                   getCategoryWeightSum(const Formation&);
  };
}