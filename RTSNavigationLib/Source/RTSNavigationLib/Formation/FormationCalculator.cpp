#include "FormationCalculator.h"

#include <glm/ext/matrix_transform.hpp>
#include <set>

#include "Body.h"
#include "Formation.h"
#include "Formation/FormationShape/FormationShape.h"
#include "UnitPlacement.h"

#include "Util/Geometry2D.h"
#include "Util/RectangleGrid/RectangleGridSvg.h"
#include "Util/RectangleGrid/RectangleGridVoxelizer.h"
#include "Util/svg.h"

namespace RTSNavigationLib
{
    FormationCalculator::FormationCalculator(const Formation& formation, const std::vector<Body>& units)
      : rootFormation(formation)
    {
        unitsLeftToPlace = summarizeUnits(units);
        overall          = unitsLeftToPlace;
    }
    FormationCalculator::FormationCalculator(const Formation& formation, const std::vector<WorldBody>& units)
      : rootFormation(formation)
    {
        unitsLeftToPlace = summarizeUnits(units);
        overall          = unitsLeftToPlace;
    }
    FormationCalculator::FormationCalculator(const Formation& formation, const std::map<Body, size_t>& units)
      : rootFormation(formation)
    {
        unitsLeftToPlace = units;
        overall          = unitsLeftToPlace;
    }

    std::vector<WorldBody> FormationCalculator::calculate()
    {
        glm::dmat4 currentTransformation = glm::dmat4(1);
        weightSumPerCategory             = getCategoryWeightSum(rootFormation);

        glm::dvec2 parentCenter         = glm::dvec2(0, 0);
        size_t     parentSize           = 1;
        double     parentRotation       = 0;
        double     parentInterfaceWidth = 0;

        std::vector<WorldBody> result         = recurse(parentCenter, parentSize, parentRotation, parentInterfaceWidth, rootFormation);
        std::vector<WorldBody> centeredResult = centerBodies(result);
        return centeredResult;
    }

    std::vector<WorldBody> FormationCalculator::recurse(const glm::dvec2& parentCenter, size_t parentSize, double parentRotation, double parentInterfaceWidth, const Formation& formation)
    {
        size_t scale           = 1;
        auto   unitsPlacedHere = gatherUnits(formation);
        auto   formationSize   = getSizeSum(unitsPlacedHere);

        std::vector<WorldBody> result;

        RectangleGrid<bool> grid;

        glm::dvec2 formationCenter = glm::dvec2(0, 0);

        int       maxTries   = 150;
        int       tries      = maxTries;
        long long lastPlaced = -1;
        bool      allPlaced  = false;
        while (!allPlaced)
        {
            if (lastPlaced == result.size())
            {
                tries--;
                if (tries <= 0)
                    break;
            }
            else
                tries = maxTries;

            lastPlaced                  = result.size();
            glm::mat4 toFormationCenter = getLocalTransformation(formation, parentCenter, parentSize, parentRotation, parentInterfaceWidth, scale);
            formationCenter             = toFormationCenter * glm::dvec4(0, 0, 0, 1);

            grid        = getGrid(formation, toFormationCenter);
            auto placer = UnitPlacement(grid, unitsPlacedHere, formation.getPlacementBehavior());
            result      = placer.place(allPlaced);
            grid        = placer.getUsedPositions();

            saveAsSvg(result, grid, lastpolygon);
            if (allPlaced)
            {
                allGrids.push_back(grid);
                allPolygons.push_back(lastpolygon);
                break;
            }
            scale++;
        }

        if (tries <= 0)
            return {};

        for (size_t i = 0; i < formation.getChildrenCount(); i++)
        {
            auto&      child       = formation.getChild(i);
            glm::dvec3 vectorScale = getScalingVector(formation, parentInterfaceWidth, parentSize);
            auto       sub         = recurse(formationCenter, scale, parentRotation, formation.getShape().getInterfaceWidth(child.getParentInterfacePoint(), vectorScale), child);
            result.insert(result.end(), sub.begin(), sub.end());
        }

        saveAsSvg(result, grid, lastpolygon);
        return result;
    }

    glm::dmat4 FormationCalculator::getLocalTransformation(const Formation&  formation,
                                                           const glm::dvec2& parentCenter,
                                                           size_t            parentScale,
                                                           double&           parentRotation,
                                                           double            parentparentInterfaceWidth,
                                                           size_t            scale)
    {
        FormationShape& shape = formation.getShape();

        glm::dvec2 parentInterfacePoint  = glm::dvec2(0, 0);
        glm::dvec2 parentInterfaceNormal = glm::dvec2(0, 1);
        double     parentInterfaceWidth  = 1;
        if (formation.hasParent())
        {
            glm::dvec3 vectorScale = getScalingVector(formation.getParent(), parentparentInterfaceWidth, parentScale);
            parentInterfacePoint   = formation.getParent().getShape().getInterfacePoint(formation.getParentInterfacePoint());
            parentInterfacePoint   = glm::dvec2(parentInterfacePoint.x * vectorScale.x, parentInterfacePoint.y * vectorScale.y);
            parentInterfaceNormal  = formation.getParent().getShape().getInterfaceNormal(formation.getParentInterfacePoint());
            parentInterfaceWidth   = formation.getParent().getShape().getInterfaceWidth(formation.getParentInterfacePoint(), vectorScale);
        }

        glm::dvec2 interfacePoint = -shape.getInterfacePoint(formation.getOwnInterfacePoint());
        glm::dmat4 result         = glm::dmat4(1);

        glm::dvec3 vectorScale = getScalingVector(formation, parentInterfaceWidth, scale);

        double rotation = formation.getRotation() + parentRotation;
        if (formation.getRotateWithInterface())
        {
            double angle = Geometry2D::getAngle(glm::dvec2(0, 1), parentInterfaceNormal);
            rotation     = parentRotation + angle;
        }

        result = glm::translate(result, glm::dvec3(parentCenter, 0));
        result = glm::translate(result, glm::dvec3(parentInterfacePoint, 0));
        result = glm::rotate(result, rotation, glm::dvec3(0, 0, 1));
        result = glm::scale(result, vectorScale);
        result = glm::translate(result, glm::dvec3(interfacePoint, 0));
        return result;
    }

    void FormationCalculator::saveAsSvg(const std::vector<WorldBody>& bodies, const RectangleGrid<bool>& grid, const std::vector<glm::dvec2>& currentPolygon)
    {
        if (!saveSVG)
            return;
        std::vector<std::string> colors = { "red", "green", "blue", "yellow", "grey", "lime", "navy", "aqua" };

        std::vector<svg> svgDebug = {}; // RectangleGridSvg::write(grid, 1);

        for (auto& x : allPolygons)
        {
            svg debug;
            debug.streak     = x;
            debug.wrapAround = true;
            debug.color      = "blue";
            debug.thickness  = 0.1;
            svgDebug.push_back(debug);
        }
        if (currentPolygon.size() != 0)
        {
            svg debug;
            debug.streak     = currentPolygon;
            debug.wrapAround = true;
            debug.color      = "red";
            debug.thickness  = 0.1;
            svgDebug.push_back(debug);
        }
        size_t counter = 0;
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
            debug.color     = colors[body.category % colors.size()];
            debug.thickness = 0.1;
            debug.text      = std::to_string(counter);
            svgDebug.push_back(debug);
            counter++;
        }
        svg::write("FormationCalculator.svg", svgDebug, glm::dvec2(-10, -10), glm::dvec2(20, 20));
    }

    RectangleGrid<bool> FormationCalculator::getGrid(const Formation& formation, const glm::dmat4& transformation)
    {
        std::vector<glm::dvec2> polygon = formation.getShape().getPolygon();

        double hollownes = 1.0 - std::min(formation.getShape().getHollow(), 1.0);
        if (hollownes != 1 && hollownes != 0)
        {
            std::vector<glm::dvec2> hollowPolygon = polygon;
            hollowPolygon.push_back(hollowPolygon[0]);
            for (auto& x : hollowPolygon)
                x *= hollownes;
            polygon.push_back(polygon[0]);
            polygon.insert(polygon.end(), hollowPolygon.begin(), hollowPolygon.end());
        }

        for (auto& x : polygon)
            x = transformation * glm::vec4(x, 0, 1);
        lastpolygon = polygon;

        auto       minMax    = getMinMax(polygon);
        glm::dvec2 centroid  = Geometry2D::findCentroid(polygon);
        glm::dvec2 span      = glm::vec2(minMax.second - minMax.first);
        glm::ivec2 dimension = glm::ivec2((int)std::ceil(span.x), (int)std::ceil(span.y)) + glm::ivec2(2, 2);
        glm::ivec2 offset    = centroid - ((glm::dvec2)dimension) / 2.0;

        auto grid = RectangleGridVoxelizer::voxelize(polygon, dimension, offset);

        for (const auto& subGrid : allGrids)
        {
            grid = grid - subGrid;
        }

        return grid;
    }

    std::pair<glm::dvec2, glm::dvec2> FormationCalculator::getMinMax(const std::vector<glm::dvec2>& polygon)
    {
        glm::dvec2 min = glm::dvec2(std::numeric_limits<double>::max(), std::numeric_limits<double>::max());
        glm::dvec2 max = glm::dvec2(-std::numeric_limits<double>::max(), -std::numeric_limits<double>::max());

        for (auto& x : polygon)
        {
            min.x = std::min(x.x, min.x);
            min.y = std::min(x.y, min.y);
            max.x = std::max(x.x, max.x);
            max.y = std::max(x.y, max.y);
        }
        return std::make_pair(min, max);
    }

    glm::dvec3 FormationCalculator::getScalingVector(const Formation& formation, double parentInterfaceWidth, size_t scale)
    {
        glm::dvec3 result;
        auto       behavior = formation.getShape().getScalingBehavior();

        switch (behavior)
        {
            case ScalingBehavior::PureX:
                result = glm::dvec3(scale, 1, 1);
                break;
            case ScalingBehavior::PureY:
                result = glm::dvec3(1, scale, 1);
                break;
            case ScalingBehavior::X25Y75:
                result = glm::dvec3(1 + scale / 4, 1 + scale - (scale % 4 == 0 ? 1 : 0), 1);
                break;
            case ScalingBehavior::X75Y25:
                result = glm::dvec3(1 + scale - (scale % 4 == 0 ? 1 : 0), 1 + scale / 4, 1);
                break;
            case ScalingBehavior::Isotropic:
            default:
                // first scale only x and than both, this hopefully allows more subtle formation grow
                bool   xScalesFirst    = scale % 2 == 0;
                size_t translatedScale = 1 + (scale - 1) / 2;
                result                 = glm::dvec3(translatedScale + (xScalesFirst ? 1 : 0), translatedScale, 1);
                break;
        }

        if (formation.getOverwriteWidthWithInterfaceWidth())
        {
            double base = formation.getShape().getBaseSize().x;
            result      = glm::dvec3(parentInterfaceWidth / base, scale, 1);
        }

        return result;
    }

    size_t FormationCalculator::getSizeSum(const std::map<Body, size_t>& units)
    {
        size_t result = 0;
        for (const auto& x : units)
        {
            result += x.first.size * x.second;
        }
        return result;
    }

    std::map<Body, size_t> FormationCalculator::gatherUnits(const Formation& formation)
    {
        std::map<Body, size_t> unitAmount;

        for (const auto& category : formation.getUnitCategories())
        {
            double weight = formation.getUnitDistributionWeight() / weightSumPerCategory[category];

            for (const auto& unit : overall)
            {
                if (unit.first.category != category)
                    continue;
                size_t amount    = (size_t)std::ceil(weight * (double)unit.second);
                size_t available = unitsLeftToPlace[unit.first];
                if (amount > available)
                    amount = available;
                unitAmount[unit.first] = amount;
                unitsLeftToPlace[unit.first] -= amount;
            }
        }
        return unitAmount;
    }

    std::map<size_t, double> FormationCalculator::getCategoryWeightSum(const Formation& formation)
    {
        std::map<size_t, double> result;
        for (const auto& category : formation.getUnitCategories())
        {
            result[category] += formation.getUnitDistributionWeight();

            for (size_t i = 0; i < formation.getChildrenCount(); i++)
            {
                auto& child = formation.getChild(i);
                auto  sub   = getCategoryWeightSum(child);
                for (auto& keyvalue : sub)
                {
                    if (result.count(keyvalue.first) == 0)
                        result[keyvalue.first] = keyvalue.second;
                    else
                        result[keyvalue.first] += keyvalue.second;
                }
            }
        }
        return result;
    }

    std::map<Body, size_t> FormationCalculator::summarizeUnits(const std::vector<Body>& units)
    {
        std::map<Body, size_t> result;
        for (auto& x : units)
        {
            if (!result.contains(x))
                result[x] = 1;
            else
                result[x]++;
        }
        return result;
    }
    std::map<Body, size_t> FormationCalculator::summarizeUnits(const std::vector<WorldBody>& units)
    {
        std::map<Body, size_t> result;
        for (auto& x : units)
        {
            Body key;
            key.size     = x.size;
            key.category = x.category;
            if (!result.contains(key))
                result[key] = 1;
            else
                result[key]++;
        }
        return result;
    }

    std::vector<WorldBody> FormationCalculator::centerBodies(const std::vector<WorldBody>& bodies)
    {
        glm::dvec2 center = glm::dvec2(0, 0);
        for (auto& x : bodies)
            center += x.position;
        center /= bodies.size();
        std::vector<WorldBody> result = bodies;
        for (auto& x : result)
            x.position -= center;
        for (auto& poly : allPolygons)
            for (auto& x : poly)
                x -= center;
        return result;
    }

    std::vector<std::vector<glm::dvec2>> FormationCalculator::getShapes() const
    {
        return allPolygons;
    }
}