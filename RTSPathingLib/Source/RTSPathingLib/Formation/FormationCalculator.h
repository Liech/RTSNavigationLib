#pragma once

#include <map>
#include <vector>
#include <glm/glm.hpp>

#include "RTSPathingLib/Util/RectangleGrid/RectangleGrid.h"
#include "RTSPathingLib/Body.h"

namespace RTSPathingLib {
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
    std::map<size_t, double> weightSumPerCategory;

    std::vector<glm::dvec2> lastpolygon;
    std::vector<std::vector<glm::dvec2>> allPolygons;

    bool saveSVG = true;

    std::vector<Body>                          recurse( const glm::dvec2& parentCenter, size_t parentSize, double parentRotation, double parentInterfaceWidth, const Formation&);
    void                                       saveAsSvg(const std::vector<Body>& bodies, const RectangleGrid<bool>& grid, const std::vector<glm::dvec2>& currentPolygon);
    glm::dvec3                                 getScalingVector(const Formation&, double parentInterfaceWidth , size_t scale);
    RectangleGrid<bool>                        getGrid(const Formation&, const glm::dmat4& transformation);
    std::pair<glm::dvec2, glm::dvec2>          getMinMax(const std::vector<glm::dvec2>&);
    glm::dmat4                                 getLocalTransformation(const Formation&, const glm::dvec2& parentCenter, size_t parentScale, double& parentRotation, double parentInterfaceWidth, size_t scale);
    size_t                                     getSizeSum(const std::map<size_t, size_t>&);
    std::map<size_t, size_t>                   gatherUnits(const Formation&);
    std::map<size_t, std::map<size_t, size_t>> getSizesPerCategory(const std::vector<Body>& units);
    std::map<size_t, double>                   getCategoryWeightSum(const Formation&);
  };
}