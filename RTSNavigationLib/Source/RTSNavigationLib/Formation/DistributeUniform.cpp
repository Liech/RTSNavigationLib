#include "DistributeUniform.h"

#include <algorithm>
#include <cassert>

namespace RTSNavigationLib
{
    std::vector<glm::ivec2> DistributeUniform::distribute(const std::vector<glm::ivec2>& places, size_t amountToPlace)
    {
        assert(places.size() >= amountToPlace);
        if (places.size() == amountToPlace)
            return places;
        auto copy = places;
        return placeRecursive(copy, amountToPlace);
    }

    std::vector<glm::ivec2> DistributeUniform::placeRecursive(std::vector<glm::ivec2>& places, size_t amountToPlace)
    {
        if (amountToPlace == 1)
            return { placeLast(places) };

        bool   yAxisIsmainAxis = findMainAxis(places);
        size_t half            = places.size() / 2;

        if (yAxisIsmainAxis)
            std::ranges::sort(places, [](const glm::ivec2& left, const glm::ivec2& right) { return std::tie(left.y, left.x) < std::tie(right.y, right.x); });
        else
            std::ranges::sort(places, [](const glm::ivec2& left, const glm::ivec2& right) { return std::tie(left.x, left.y) < std::tie(right.x, right.y); });

        auto   left        = std::vector<glm::ivec2>(places.begin(), places.begin() + half);
        auto   right       = std::vector<glm::ivec2>(places.begin() + half, places.end());
        size_t leftAmount  = amountToPlace / 2;
        size_t rightAmount = amountToPlace - leftAmount;

        std::vector<glm::ivec2> result;

        auto leftResult  = placeRecursive(left, leftAmount);
        auto rightResult = placeRecursive(right, rightAmount);

        result.insert(result.end(), leftResult.begin(), leftResult.end());
        result.insert(result.end(), rightResult.begin(), rightResult.end());

        return result;
    }

    glm::ivec2 DistributeUniform::placeLast(const std::vector<glm::ivec2>& places) {
        glm::dvec2 center = getCenter(places);
        
        double     bestDistance = std::numeric_limits<double>::infinity();
        glm::ivec2 bestResult   = places[0];

        for (const auto& x : places)
        {
            double dist = glm::distance(center, glm::dvec2(x));
            if (dist < bestDistance)
            {
                bestDistance = dist;
                bestResult = x;
            }
        }

        return bestResult;
    }

    bool DistributeUniform::findMainAxis(const std::vector<glm::ivec2>& places)
    {
        glm::dvec2 center = getCenter(places);

        glm::dvec2 cumVec = glm::dvec2(0, 0);
        for (const auto& x : places)
        {
            auto dir = glm::dvec2(x) - center;
            cumVec += glm::dvec2(std::abs(dir.x), std::abs(dir.y));
        }
        cumVec = glm::normalize(cumVec);
        return std::abs(cumVec.y) > std::abs(cumVec.x);
    }

    glm::dvec2 DistributeUniform::getCenter(const std::vector<glm::ivec2>& places)
    {
        glm::dvec2 center = glm::dvec2(0, 0);
        for (const auto& x : places)
            center += x;
        center /= places.size();
        return center;
    }

}