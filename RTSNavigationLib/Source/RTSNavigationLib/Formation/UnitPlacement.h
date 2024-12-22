#pragma once

#include <map>
#include <vector>

#include "RTSNavigationLib/Formation/UnitPlacementBehavior.h"
#include "RTSNavigationLib/Util/RectangleGrid/RectangleGrid.h"

namespace RTSNavigationLib
{
    struct Body;
    struct WorldBody;

    class UnitPlacement
    {
      public:
        UnitPlacement(const RectangleGrid<bool>&, const std::map<Body, size_t>&, UnitPlacementBehavior = UnitPlacementBehavior::CenterFirst);

        std::vector<WorldBody> place(bool& success);

        RectangleGrid<bool> getUsedPositions() const;

      private:
        std::vector<WorldBody>  placeSizeN(size_t size, size_t amount, bool& success);
        std::vector<WorldBody>  placeSize1(bool& success);
        void                    assignCategories(std::vector<WorldBody>&, size_t size);
        std::vector<glm::ivec2> getAllPlaces(const RectangleGrid<bool>&);

        std::vector<glm::ivec2> centerSort(const std::vector<glm::ivec2>&) const;
        std::vector<glm::ivec2> distributeSort(const std::vector<glm::ivec2>&, size_t desired) const;

        bool saveSVG = false;

        void saveAsSvg(const std::vector<WorldBody>&);

        const RectangleGrid<bool>&    grid;
        const std::map<Body, size_t>& unitsToPlace;
        RectangleGrid<bool>           usedPositions;
        size_t                        smallestSize = 1;
        UnitPlacementBehavior         placementBehavior;
    };
}