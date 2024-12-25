#include "DistributeUniform.h"

#include <algorithm>
#include <cassert>
#include <unordered_set>

namespace RTSNavigationLib
{
    std::vector<glm::ivec2> DistributeUniform::distribute(const std::vector<glm::ivec2>& places, size_t amountToPlace)
    {
        assert(places.size() >= amountToPlace);
        if (places.size() == amountToPlace)
            return places;
        std::vector<size_t> index;
        std::unordered_set<size_t>    unplaced;
        index.reserve(places.size());
        for (size_t i = 0; i < places.size(); i++)
            index.push_back(i);
        unplaced.insert(index.begin(),index.end());

        auto placementResult = placeRecursive(index, places, amountToPlace);
        assert(placementResult.size() == amountToPlace);

        // placementresult is amountToPlace long, rest must be appended
        std::vector<glm::ivec2> result;
        result.resize(places.size());
        size_t           i = 0;
        for (; i < placementResult.size(); i++)
        {
            unplaced.erase(placementResult[i]);
            result[i] = places[placementResult[i]];
        }
        for (const auto& x : unplaced)
        {
            result[i] = places[x];
            i++;
        }
        assert(result.size() == places.size());
        return result;
    }

    std::vector<size_t> DistributeUniform::placeRecursive(std::vector<size_t>& indexes, const std::vector<glm::ivec2>& places, size_t amountToPlace)
    {
        if (amountToPlace == 1)
            return { placeLast(indexes,places) };

        bool   yAxisIsmainAxis = findMainAxis(indexes,places);
        size_t half            = indexes.size() / 2;

        if (yAxisIsmainAxis)
            std::ranges::sort(indexes, [&places](const size_t& left, const size_t& right) { return std::tie(places[left].y, places[left].x) < std::tie(places[right].y, places[right].x); });
        else
            std::ranges::sort(indexes, [&places](const size_t& left, const size_t& right) { return std::tie(places[left].x, places[left].y) < std::tie(places[right].x, places[right].y); });

        auto   left        = std::vector<size_t>(indexes.begin(), indexes.begin() + half);
        auto   right       = std::vector<size_t>(indexes.begin() + half, indexes.end());
        size_t leftAmount  = amountToPlace / 2;
        size_t rightAmount = amountToPlace - leftAmount;

        std::vector<size_t> result;

        auto leftResult  = placeRecursive(left,places, leftAmount);
        auto rightResult = placeRecursive(right,places, rightAmount);

        result.insert(result.end(), leftResult.begin(), leftResult.end());
        result.insert(result.end(), rightResult.begin(), rightResult.end());

        return result; 
    }

    size_t DistributeUniform::placeLast(std::vector<size_t>& indexes, const std::vector<glm::ivec2>& places)
    {
        glm::dvec2 center = getCenter(indexes,places);

        double     bestDistance = std::numeric_limits<double>::infinity();
        size_t bestResult   = indexes[0];

        for (const auto& x : indexes)
        {
            double dist = glm::distance(center, glm::dvec2(places[x]));
            if (dist < bestDistance)
            {
                bestDistance = dist;
                bestResult   = x;
            }
        }

        return bestResult;
    }

    bool DistributeUniform::findMainAxis(std::vector<size_t>& indexes, const std::vector<glm::ivec2>& places)
    {
        glm::dvec2 center = getCenter(indexes,places);

        glm::dvec2 cumVec = glm::dvec2(0, 0);
        for (const auto& x : indexes)
        {
            auto dir = glm::dvec2(places[x]) - center;
            cumVec += glm::dvec2(std::abs(dir.x), std::abs(dir.y));
        }
        cumVec = glm::normalize(cumVec);
        return std::abs(cumVec.y) > std::abs(cumVec.x);
    }

    glm::dvec2 DistributeUniform::getCenter(std::vector<size_t>& indexes, const std::vector<glm::ivec2>& places)
    {
        glm::dvec2 center = glm::dvec2(0, 0);
        for (const auto& x : indexes)
            center += places[x];
        center /= indexes.size();
        return center;
    }

}