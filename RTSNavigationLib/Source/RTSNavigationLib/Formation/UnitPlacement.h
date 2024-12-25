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
        UnitPlacement(const RectangleGrid<bool>&,
                      const std::map<Body, size_t>&,
                      double                rotation          = 0,
                      UnitPlacementBehavior cutBehavior       = UnitPlacementBehavior::FrontFirst,
                      UnitPlacementBehavior placementBehavior = UnitPlacementBehavior::DistributeEvenly);

        std::vector<WorldBody> place(bool& success);

        RectangleGrid<bool> getUsedPositions() const;

      private:
        std::vector<glm::ivec2> placeSizeN(size_t size, size_t amount, bool& success);
        std::vector<WorldBody>  assignCategories(std::vector<glm::ivec2>&, size_t size);
        bool                    cutPlaces();

        std::vector<glm::ivec2> rankSortPlaces(std::vector<glm::ivec2>&, size_t amountUsed, UnitPlacementBehavior strategy);
        std::vector<glm::ivec2> centerSort(const std::vector<glm::ivec2>&) const;
        std::vector<glm::ivec2> distributeSort(const std::vector<glm::ivec2>&, size_t amountUsed) const;

        std::vector<glm::ivec2> getPossiblePositions(size_t size);

        bool saveSVG = false;

        void saveAsSvg(const std::vector<WorldBody>&);

        const RectangleGrid<bool>&    grid;
        const std::map<Body, size_t>& unitsToPlace;
        RectangleGrid<bool>           usedPositions;
        size_t                        smallestSize = 1;
        size_t                        overallSize  = 0;
        UnitPlacementBehavior         placementBehavior;
        UnitPlacementBehavior         cutBehavior;
        double                        rotation;
    };
}