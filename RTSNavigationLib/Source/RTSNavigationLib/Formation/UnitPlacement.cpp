#include "UnitPlacement.h"

#include <algorithm>
#include <set>
#include <stdexcept>

#include "Body.h"
#include "WorldBody.h"
#include "Util/svg.h"

namespace RTSNavigationLib
{
    UnitPlacement::UnitPlacement(const RectangleGrid<bool>& unitGrid, const std::map<Body, size_t>& unitList, UnitPlacementBehavior placementStrategy)
      : grid(unitGrid)
      , unitsToPlace(unitList)
    {
        placementBehavior = placementStrategy;

        usedPositions.dimension = grid.dimension;
        usedPositions.offset    = grid.offset;
        usedPositions.data.resize(grid.data.size());

        smallestSize = std::numeric_limits<size_t>::max();
        for (auto& x : unitList)
        {
            smallestSize = std::min(smallestSize, x.first.size);
        }
    }

    std::vector<WorldBody> UnitPlacement::place(bool& success)
    {
        success = false;

        std::vector<WorldBody> result;

        std::set<size_t> sizes;
        for (const auto& x : unitsToPlace)
        {
            if (x.first.size != 1)
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
            assignCategories(sub, sizeVec[i]);
            result.insert(result.end(), sub.begin(), sub.end());
        }

        auto size1 = placeSize1(success);
        if (!success)
            return {};
        assignCategories(size1, 1);
        result.insert(result.end(), size1.begin(), size1.end());

        success = true;
        saveAsSvg(result);
        return result;
    }

    void UnitPlacement::assignCategories(std::vector<WorldBody>& input, size_t size)
    {
        size_t position = 0;
        for (const auto& x : unitsToPlace)
        {
          if (x.first.size == size && x.second > 0)
          {
              for (size_t i = 0;i < x.second && position < input.size();i++)
              {
                  input[position].category = x.first.category;
                  position++;              
              }
            }
        }
    }

    std::vector<WorldBody> UnitPlacement::placeSizeN(size_t size, size_t amount, bool& success)
    {
        std::vector<WorldBody> result;
        RectangleGrid<bool> possiblePlaces = grid - usedPositions;
        auto                get            = [&possiblePlaces](const glm::ivec2& pos) { return possiblePlaces.data[pos.x + pos.y * possiblePlaces.dimension.x]; };
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
            }
            possiblePlaces.data[i] = ok;
        }
        auto possible = getAllPlaces(possiblePlaces);
        if (possible.size() < amount)
        {
            success = false;
            return {};
        }

        if (smallestSize == size && placementBehavior != UnitPlacementBehavior::DistributeEvenly)
        {
            possible = centerSort(possible);
            if (placementBehavior == UnitPlacementBehavior::OuterFirst)
                std::reverse(possible.begin(), possible.end());
        }
        else
            possible = distributeSort(possible, amount);

        for (size_t i = 0; i < amount; i++)
        {
            WorldBody sub;
            sub.category = 0;
            sub.size     = size;
            sub.position = (glm::dvec2)possible[i] + (glm::dvec2)grid.offset + glm::dvec2(size, size) / 2.0;
            result.push_back(sub);

            for (size_t x = 0; x < size && x + possible[i].x < grid.dimension.x; x++)
                for (size_t y = 0; y < size && y + possible[i].y < grid.dimension.y; y++)
                {
                    usedPositions.data[(possible[i].x + x) + (possible[i].y + y) * grid.dimension.x] = true;
                }
        }

        success = true;
        return result;
    }

    std::vector<glm::ivec2> UnitPlacement::getAllPlaces(const RectangleGrid<bool>& places)
    {
        std::vector<glm::ivec2> result;
        for (size_t i = 0; i < places.data.size(); i++)
        {
            if (places.data[i])
                result.push_back(glm::ivec2(i % places.dimension.x, i / places.dimension.x));
        }
        return result;
    }

    std::vector<WorldBody> UnitPlacement::placeSize1(bool& success)
    {
        std::vector<WorldBody> result;
        size_t            currentSize = 1;

        size_t requiredAmount = 0;

        for (const auto& x : unitsToPlace)
        {
            requiredAmount += x.second;
        }

        auto unused   = grid - usedPositions;
        auto possible = getAllPlaces(unused);

        if (placementBehavior != UnitPlacementBehavior::DistributeEvenly)
            possible = centerSort(possible);
        else
            throw std::runtime_error("Not yet reimplemented!");
        // possible = distributeSort(possible, amountUnits);
        if (placementBehavior == UnitPlacementBehavior::OuterFirst)
            std::reverse(possible.begin(), possible.end());

        if (requiredAmount > possible.size())
        {
            success = false;
            return {};
        }

        size_t currentCategory = 0;
        if (requiredAmount == 0)
        {
            success = true;
            return {};
        }
        for (auto pos : possible)
        {
            WorldBody sub;
            sub.category = 0;
            sub.size     = currentSize;
            sub.position = (glm::dvec2)pos + (glm::dvec2)grid.offset + glm::dvec2(0.5, 0.5);
            result.push_back(sub);
            usedPositions.data[pos.x + pos.y * grid.dimension.x] = true;
            requiredAmount--;
            if (requiredAmount == 0)
                break;
        }
        success = true;
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
    std::vector<glm::ivec2> UnitPlacement::distributeSort(const std::vector<glm::ivec2>& input, size_t desired) const
    {
        auto current = centerSort(input);
        if (desired <= 2)
            return current;
        std::vector<glm::ivec2> result = { current[0] };
        current.erase(current.begin() + 0);

        while (current.size() > 0)
        {
            std::sort(current.begin(),
                      current.end(),
                      [&result](const glm::ivec2& a, const glm::ivec2& b)
                      {
                          double distanceSumA = 0;
                          double distanceSumB = 0;
                          for (auto& x : result)
                          {
                              distanceSumA += glm::distance((glm::dvec2)a, (glm::dvec2)x);
                              distanceSumB += glm::distance((glm::dvec2)b, (glm::dvec2)x);
                          }
                          return distanceSumA > distanceSumB;
                      });
            result.push_back(current[0]);
            current.erase(current.begin() + 0);
        }

        return result;
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