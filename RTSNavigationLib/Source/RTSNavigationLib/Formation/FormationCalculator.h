#pragma once

#include <glm/glm.hpp>
#include <map>
#include <vector>

#include "RTSNavigationLib/Body.h"
#include "RTSNavigationLib/Util/RectangleGrid/RectangleGrid.h"
#include "RTSNavigationLib/WorldBody.h"

namespace RTSNavigationLib
{
    class Formation;

    struct FormationCalculator_formation_input
    {
        glm::dvec2       parentCenter;
        size_t           parentSize;
        double           parentRotation;
        double           parentInterfaceWidth;
        const Formation* formation;
    };

    class FormationCalculator
    {
      public:
        FormationCalculator(const Formation&, const std::vector<Body>& units);
        FormationCalculator(const Formation&, const std::vector<WorldBody>& units);
        FormationCalculator(const Formation&, const std::map<Body, size_t>& units);

        std::vector<WorldBody> calculate();

        std::vector<std::vector<glm::dvec2>> getShapes() const;
        std::vector<std::vector<glm::dvec2>> getDebugShapes() const;

      private:
        const Formation& rootFormation;

        std::map<Body, size_t>           overall;
        std::map<Body, size_t>           unitsLeftToPlace;
        std::vector<RectangleGrid<bool>> allGrids;
        std::map<size_t, double>         weightSumPerCategory;

        std::vector<glm::dvec2>              lastpolygon;
        std::vector<std::vector<glm::dvec2>> allPolygons;
        std::vector<std::vector<glm::dvec2>> debugPolys;

        bool saveSVG       = false;

        std::vector<WorldBody>            recurse(const FormationCalculator_formation_input& input);
        bool                              recurse_try(const FormationCalculator_formation_input& input,
                                                      size_t                                     scale,
                                                      const std::map<Body, size_t>&              unitsPlacedHere,
                                                      glm::dvec2&                                formationCenter,
                                                      std::vector<WorldBody>&                    result,
                                                      bool                                       saveOnSuccess = true);
        void                              saveAsSvg(const std::vector<WorldBody>& bodies, const RectangleGrid<bool>& grid, const std::vector<glm::dvec2>& currentPolygon);
        glm::dvec3                        getScalingVector(const Formation&, double parentInterfaceWidth, size_t scale);
        RectangleGrid<bool>               getGrid(const Formation&, const glm::dmat4& transformation);
        std::pair<glm::dvec2, glm::dvec2> getMinMax(const std::vector<glm::dvec2>&);
        glm::dmat4               getLocalTransformation(const Formation&, const glm::dvec2& parentCenter, size_t parentScale, double& parentRotation, double parentInterfaceWidth, size_t scale);
        size_t                   getSizeSum(const std::map<Body, size_t>&);
        std::map<Body, size_t>   gatherUnits(const Formation&);
        std::map<Body, size_t>   summarizeUnits(const std::vector<Body>& units);
        std::map<Body, size_t>   summarizeUnits(const std::vector<WorldBody>& units);
        std::map<size_t, double> getCategoryWeightSum(const Formation&);
        std::vector<WorldBody>   centerBodies(const std::vector<WorldBody>& bodies);
    };
}