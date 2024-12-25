#include "UnitPlacement.h"

#include <algorithm>
#include <glm/ext/matrix_transform.hpp>
#include <set>
#include <stdexcept>

#include "Body.h"
#include "DistributeUniform.h"
#include "Util/svg.h"
#include "WorldBody.h"

namespace RTSNavigationLib
{
    UnitPlacement::UnitPlacement(const RectangleGrid<bool>&    unitGrid,
                                 const std::map<Body, size_t>& unitList,
                                 double                        rotation_,
                                 UnitPlacementBehavior         cutStrategy,
                                 UnitPlacementBehavior         placementStrategy)
      : grid(unitGrid)
      , unitsToPlace(unitList)
    {
        placementBehavior = placementStrategy;
        cutBehavior       = cutStrategy;
        rotation          = rotation_;

        usedPositions.dimension = grid.dimension;
        usedPositions.offset    = grid.offset;
        usedPositions.data.resize(grid.data.size());
        cutPositions = usedPositions;

        overallSize  = 0;
        smallestSize = std::numeric_limits<size_t>::max();
        for (auto& x : unitList)
        {
            smallestSize = std::min(smallestSize, x.first.size);
            overallSize += x.second * x.first.size * x.first.size;
        }
    }

    std::vector<WorldBody> UnitPlacement::place(bool& success)
    {
        success = false;

        if (grid.data.size() < overallSize)
            return {};

        bool cutSuccess = cutPlaces();
        if (!cutSuccess)
            return {};

        std::vector<WorldBody> result;

        std::set<size_t> sizes;
        for (const auto& x : unitsToPlace)
        {
            sizes.insert(x.first.size);
        }
        std::vector<size_t> sizeVec = std::vector<size_t>(sizes.begin(), sizes.end());
        std::sort(sizeVec.begin(), sizeVec.end());

        for (int i = sizeVec.size() - 1; i >= 0; i--)
        {
            size_t amountToPlace = 0;
            for (const auto& x : unitsToPlace)
                if (x.first.size == sizeVec[i])
                    amountToPlace += x.second;
            auto sub = placeSizeN(sizeVec[i], amountToPlace, success);
            if (!success)
                return {};
            auto bodies = assignCategories(sub, sizeVec[i]);
            result.insert(result.end(), bodies.begin(), bodies.end());
        }

        success = true;
        saveAsSvg(result);
        return result;
    }

    std::vector<WorldBody> UnitPlacement::assignCategories(std::vector<glm::ivec2>& input, size_t size)
    {
        std::vector<WorldBody> result;
        for (const auto& x : unitsToPlace)
        {
            if (x.first.size == size && x.second > 0)
            {
                input = rankSortPlaces(input, x.second, placementBehavior);
                for (size_t i = 0; i < x.second; i++)
                {
                    WorldBody sub;
                    sub.category = x.first.category;
                    sub.size     = size;
                    sub.position = (glm::dvec2)input[i] + (glm::dvec2)grid.offset + glm::dvec2(size, size) / 2.0;

                    result.push_back(sub);
                }
                input.erase(input.begin(), input.begin() + x.second);
            }
        }
        return result;
    }

    std::vector<glm::ivec2> UnitPlacement::placeSizeN(size_t size, size_t amount, bool& success)
    {
        std::vector<glm::ivec2> result;
        auto                    places = getPossiblePositions(size);
        if (places.size() < amount)
        {
            success = false;
            return {};
        }
        places = rankSortPlaces(places, amount, placementBehavior);

        for (size_t i = 0; i < amount; i++)
        {
            result.push_back(places[i]);

            for (size_t x = 0; x < size && x + places[i].x < grid.dimension.x; x++)
                for (size_t y = 0; y < size && y + places[i].y < grid.dimension.y; y++)
                {
                    usedPositions.data[(places[i].x + x) + (places[i].y + y) * grid.dimension.x] = true;
                }
        }

        success = true;
        return result;
    }

    std::vector<glm::ivec2> UnitPlacement::rankSortPlaces(std::vector<glm::ivec2>& places, size_t amountUsed, UnitPlacementBehavior strategy)
    {
        switch (strategy)
        {
            case UnitPlacementBehavior::FrontFirst:
            case UnitPlacementBehavior::RearFirst:
                glm::dvec2 direction = glm::rotate(glm::dmat4(1), rotation, glm::dvec3(0, 0, 1)) * glm::dvec4(0, 1, 0, 1);
                std::ranges::sort(places, [direction](const glm::ivec2& a, const glm::ivec2& b) { return glm::dot(direction, glm::dvec2(a)) < glm::dot(direction, glm::dvec2(b)); });
                if (strategy == UnitPlacementBehavior::RearFirst)
                    std::ranges::reverse(places);
                return places;
            case UnitPlacementBehavior::DistributeEvenly:
                return distributeSort(places, amountUsed);
            case UnitPlacementBehavior::CenterFirst:
            case UnitPlacementBehavior::OuterFirst:
            default:
                auto result = centerSort(places);
                if (placementBehavior == UnitPlacementBehavior::OuterFirst)
                    std::ranges::reverse(result);
                return result;
        }
    }

    bool UnitPlacement::cutPlaces()
    {
        // gather all positions
        std::vector<glm::ivec2> positions;
        for (size_t i = 0; i < grid.data.size(); i++)
        {
            if (grid.data[i])
            {
                glm::ivec2 pos = glm::ivec2(i % grid.dimension.x, i / grid.dimension.x);
                positions.push_back(pos);
            }
        }

        if (positions.size() < overallSize)
            return false;

        // rank them
        positions = rankSortPlaces(positions, overallSize, cutBehavior);


        // mark unecessary positions as used
        size_t currentPlace = 0;
        for (size_t i = overallSize; i < positions.size(); i++)
        {
            const auto& pos                                      = positions[i];
            cutPositions.data[pos.x + pos.y * grid.dimension.x] = true;
        }
        return true;
    }

    std::vector<glm::ivec2> UnitPlacement::getPossiblePositions(size_t size)
    {
        std::vector<glm::ivec2> result;
        RectangleGrid<bool>     possiblePlaces = (grid - usedPositions) - cutPositions;

        auto get = [&possiblePlaces](const glm::ivec2& pos) -> bool { return possiblePlaces.data[pos.x + pos.y * possiblePlaces.dimension.x]; };

        for (size_t i = 0; i < possiblePlaces.data.size(); i++)
        {
            if (!possiblePlaces.data[i])
                continue;
            glm::ivec2 pos = glm::ivec2(i % grid.dimension.x, i / grid.dimension.x);
            bool       ok  = true;
            for (size_t x = 0; x < size; x++)
                for (size_t y = 0; y < size; y++)
                {
                    bool inBoundX = x + pos.x < grid.dimension.x;
                    bool inBoundY = y + pos.y < grid.dimension.y;
                    ok &= inBoundX && inBoundY && get(pos + glm::ivec2(x, y));
                }
            if (ok)
            {
                for (size_t x = 0; x < size && x + pos.x < grid.dimension.x; x++)
                    for (size_t y = 0; y < size && y + pos.y < grid.dimension.y; y++)
                    {
                        possiblePlaces.data[(pos.x + x) + (pos.y + y) * grid.dimension.x] = false;
                    }
                result.push_back(pos);
            }
        }

        return result;
    }

    std::vector<glm::ivec2> UnitPlacement::centerSort(const std::vector<glm::ivec2>& input) const
    {
        auto result = input;

        glm::dvec2 center = glm::dvec2(0, 0);
        for (auto& x : input)
            center += (glm::dvec2)x;
        center = glm::dvec2(center.x / (double)input.size(), center.y / (double)input.size());

        std::sort(result.begin(), result.end(), [center](const glm::ivec2& a, const glm::ivec2& b) { return glm::distance((glm::dvec2)a, center) < glm::distance((glm::dvec2)b, center); });
        return result;
    }

    // sort for bigger units. tries to distribute evenly
    std::vector<glm::ivec2> UnitPlacement::distributeSort(const std::vector<glm::ivec2>& input, size_t amountUsed) const
    {
        return DistributeUniform::distribute(input, amountUsed);
    }

    RectangleGrid<bool> UnitPlacement::getUsedPositions() const
    {
        return usedPositions;
    }

    void UnitPlacement::saveAsSvg(const std::vector<WorldBody>& bodies)
    {
        if (!saveSVG)
            return;

        std::vector<svg> svgDebug = {}; // RectangleGridSvg::write(grid, 1);

        for (auto& body : bodies)
        {
            svg debug;
            debug.streak = {
                body.position + glm::dvec2(-0.5, -0.5) * (double)body.size * 0.5,
                body.position + glm::dvec2(0.5, -0.5) * (double)body.size * 0.5,
                body.position + glm::dvec2(0.5, 0.5) * (double)body.size * 0.5,
                body.position + glm::dvec2(-0.5, 0.5) * (double)body.size * 0.5,
            };
            debug.filled    = true;
            debug.color     = "red";
            debug.thickness = 0.1;
            svgDebug.push_back(debug);
        }

        glm::dvec2 min = glm::dvec2(std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity());
        glm::dvec2 max = glm::dvec2(-std::numeric_limits<double>::infinity(), -std::numeric_limits<double>::infinity());

        for (auto& x : bodies)
        {
            min.x = std::min(min.x, x.position.x);
            min.y = std::min(min.y, x.position.y);
            max.x = std::max(max.x, x.position.x);
            max.y = std::max(max.y, x.position.y);
        }

        svg::write("UnitPlacement.svg", svgDebug, min + glm::dvec2(-1, -1), max + glm::dvec2(1, 1));
    }
}