#include "FormationCalculator.h"

#include <glm/ext/matrix_transform.hpp>

#include "Formation.h"
#include "Body.h"
#include "Formation/FormationShape/FormationShape.h"
#include "Util/Geometry2D.h"

#include "Util/svg.h"
#include "Util/RectangleGrid/RectangleGridVoxelizer.h"
#include "Util/RectangleGrid/RectangleGridSvg.h"

namespace RTSPathingLib {
  std::vector<Body> FormationCalculator::calculate(const Formation& formation, const std::vector<Body>& units) {
    glm::dmat4 currentTransformation = glm::dmat4(1);
    auto overall = getSizesPerCategory(units);
    auto current = overall;
    std::vector<RectangleGrid<bool>> allGrids;

    glm::dvec2 startPoint = glm::dvec2(0, 0);
    std::vector<Body> result = formate(current,overall, startPoint,formation, allGrids);
   

    return result;
  }

  std::vector<glm::dvec2> lastpolygon;

  std::vector<Body> FormationCalculator::formate(std::map<size_t, std::map<size_t, size_t>>& current, const std::map<size_t, std::map<size_t, size_t>>& overall, const glm::dvec2& startPoint, const Formation& formation, std::vector<RectangleGrid<bool>>& allGrids) {
    size_t scale             = 1;
    auto  unitsPlacedHere    = gatherUnits(formation, overall, current);
    auto  formationSize      = getSizeSum(unitsPlacedHere);
    std::vector<Body> result;

    glm::dmat4 toFormationCenter;
    RectangleGrid<bool> grid;

    int maxTries = 50;
    int tries = maxTries;
    long long lastPlaced = -1;
    bool allPlaced = false;
    while (!allPlaced) {
      if (lastPlaced == result.size()) {
        tries--;
        if (tries <= 0)
          break;
      }
      else 
        tries = maxTries;

      lastPlaced = result.size();
      toFormationCenter = getLocalTransformation(formation, startPoint, scale);
      
      std::vector<glm::dvec2> polygon;
      grid = getGrid(formation, toFormationCenter, polygon, allGrids);
      result = placeUnits(grid, unitsPlacedHere, grid.offset, formation.getUnitCategory(), allPlaced);
      lastpolygon = polygon;

      //saveAsSvg(result, allGrids, grid, polygon);
      if (allPlaced) {
        allGrids.push_back(grid);
        break;
      }
      scale ++;      
    }

    if (tries <= 0)
      return {};

    glm::dvec2 formationCenter = toFormationCenter * glm::dvec4(0, 0, 0, 1);
    for (size_t i = 0; i < formation.getChildrenCount(); i++) {
      auto& child = formation.getChild(i);

      glm::dmat4 deeper      = glm::dmat4(1);
      glm::dvec3 vectorScale = getScalingVector(formation, scale);
      glm::dvec2 parentInterfacePoint = formation.getShape().getInterfacePoint(child.getParentInterfacePoint());

      deeper = glm::rotate   (deeper, formation.getRotation(), glm::dvec3(0, 0, 1));
      deeper = glm::scale    (deeper, vectorScale);
      deeper = glm::translate(deeper, glm::dvec3(parentInterfacePoint.x, parentInterfacePoint.y, 0));

      glm::dvec2 nextOffset = deeper * glm::dvec4(0, 0, 0, 1);

      auto sub = formate(current, overall, formationCenter- nextOffset, child, allGrids);
      result.insert(result.end(), sub.begin(), sub.end());
    }

    saveAsSvg(result, allGrids, grid, lastpolygon);
    return result;
  }
  
  
  void FormationCalculator::saveAsSvg(const std::vector<Body>& bodies, std::vector<RectangleGrid<bool>>& allGrids, const RectangleGrid<bool>& grid,const std::vector<glm::dvec2>& currentPolygon) {
    //https://graphviz.org/doc/info/colors.html
    std::vector<std::string> colors = { "red", "green", "blue", "yellow", "grey", "lime", "navy", "aqua" };

    auto svgDebug = RectangleGridSvg::write(grid, 1);
    if (currentPolygon.size() != 0) {
      svg debug;
      debug.streak = currentPolygon;
      debug.wrapAround = true;
      debug.color = "red";
      debug.thickness = 0.1;
      svgDebug.push_back(debug);
    }
    for (auto& body : bodies) {
      svg debug;
      debug.streak = {
            body.position + glm::dvec2(-0.5 ,-0.5) * (double)body.size * 0.5,
            body.position + glm::dvec2( 0.5 ,-0.5) * (double)body.size * 0.5,
            body.position + glm::dvec2( 0.5 , 0.5) * (double)body.size * 0.5,
            body.position + glm::dvec2(-0.5 , 0.5) * (double)body.size * 0.5,
      };
      debug.filled = true;
      debug.color = colors[body.category%colors.size()];
      debug.thickness = 0.1;
      svgDebug.push_back(debug);
    }
    svg::write("FormationCalculator.svg", svgDebug, glm::dvec2(-10, -10), glm::dvec2(20, 20));
  }

  RectangleGrid<bool> FormationCalculator::getGrid(const Formation& formation, const glm::dmat4& transformation, std::vector<glm::dvec2>& polygon, const std::vector<RectangleGrid<bool>>& allGrids) {
    polygon = formation.getShape().getPolygon();
    for (auto& x : polygon)
      x = transformation*glm::vec4(x, 0, 1);

    auto        minMax    = getMinMax(polygon);
    glm::dvec2  centroid  = Geometry2D::findCentroid(polygon);
    glm::dvec2  span      = glm::vec2(minMax.second - minMax.first);
    glm::ivec2  dimension = glm::ivec2((int)std::ceil(span.x),(int)std::ceil(span.y)) + glm::ivec2(2, 2);
    glm::ivec2  offset    = centroid - ((glm::dvec2)dimension)/2.0;

    auto grid = RectangleGridVoxelizer::voxelize(polygon, dimension, offset);


    for (const auto& subGrid : allGrids) {
      grid = grid - subGrid;
    }

    return grid;
  }

  std::vector<Body> FormationCalculator::placeUnits(RectangleGrid<bool>& grid, const std::map<size_t, size_t>& units, const glm::dvec2& offset, size_t category, bool& allPlaced) {
    std::vector<Body> result;
    size_t currentSize = 1;
    RectangleGrid<bool> actuallyPlaced;
    actuallyPlaced.dimension = grid.dimension;
    actuallyPlaced.offset = grid.offset;
    actuallyPlaced.data.resize(grid.data.size());
    long long unitsToPlace = (long long)units.at(currentSize);
    for (size_t i = 0; i < grid.data.size() && unitsToPlace>0; i++) {
      if (grid.data[i]) {
        glm::ivec2 pos = glm::ivec2(i % grid.dimension.x, (i / grid.dimension.x) % grid.dimension.y);
        Body sub;
        sub.category = category;
        sub.size = currentSize;
        sub.position = (glm::dvec2)pos + offset + glm::dvec2(0.5,0.5);
        result.push_back(sub);
        actuallyPlaced.data[i] = true;
        unitsToPlace--;
      }      
    }
    if (unitsToPlace <= 0)
      allPlaced = true;
    grid = actuallyPlaced;
    return result;
  }

  std::pair<glm::dvec2, glm::dvec2> FormationCalculator::getMinMax(const std::vector<glm::dvec2>& polygon) {
    glm::dvec2 min = glm::dvec2( std::numeric_limits<double>::max(), std::numeric_limits<double>::max());
    glm::dvec2 max = glm::dvec2(-std::numeric_limits<double>::max(),-std::numeric_limits<double>::max());

    for (auto& x : polygon) {
      min.x = std::min(x.x, min.x);
      min.y = std::min(x.y, min.y);
      max.x = std::max(x.x, max.x);
      max.y = std::max(x.y, max.y);
    }
    return std::make_pair(min, max);
  }

  //rotation, parent transformation etc missing
  glm::dmat4 FormationCalculator::getLocalTransformation(const Formation& formation, const glm::dvec2& startPoint, size_t scale) {
    FormationShape& shape = formation.getShape();

    glm::dvec2 interfacePoint = shape.getInterfacePoint(formation.getOwnInterfacePoint());
    glm::dmat4 result = glm::dmat4(1);

    glm::dvec3 vectorScale = getScalingVector(formation, scale);

    result = glm::translate(result, glm::dvec3(startPoint.x, startPoint.y, 0));
    result = glm::rotate(result, formation.getRotation(), glm::dvec3(0, 0, 1));
    result = glm::scale(result, vectorScale);
    result = glm::translate(result, glm::dvec3(interfacePoint.x, interfacePoint.y, 0));
    return result;
  }

  glm::dvec3 FormationCalculator::getScalingVector(const Formation& formation, size_t scale) {
    glm::dvec3 result;
    switch (formation.getShape().getScalingBehavior()) {
    case ScalingBehavior::PureX:
      result = glm::vec3(scale, 1, 1);
      break;
    case ScalingBehavior::PureY:
      result = glm::vec3(1, scale, 1);
      break;
    case ScalingBehavior::X25Y75:
      result = glm::vec3(1 + scale / 4, 1 + scale - (scale % 4 == 0 ? 1 : 0), 1);
      break;
    case ScalingBehavior::X75Y25:
      result = glm::vec3(1 + scale - (scale % 4 == 0 ? 1 : 0), 1 + scale / 4, 1);
      break;
    case ScalingBehavior::Isotropic:
    default:
      //first scale only x and than both, this hopefully allows more subtle formation grow
      bool   xScalesFirst = scale % 2 == 0;
      size_t translatedScale = 1 + (scale - 1) / 2;
      result = glm::vec3(translatedScale + (xScalesFirst ? 1 : 0), translatedScale, 1);
      break;
    }
    return result;
  }

  size_t FormationCalculator::getSizeSum(const std::map<size_t, size_t>& units) {
    size_t result = 0;
    for (const auto& x : units) {
      result += x.first * x.second;
    }
    return result;
  }

  std::map<size_t, size_t> FormationCalculator::gatherUnits(const Formation& formation, const std::map<size_t, std::map<size_t, size_t>>& OverallUnits, std::map<size_t, std::map<size_t, size_t>>& availableUnits) {
    size_t category = formation.getUnitCategory();
    double weight = formation.getUnitDistributionWeight();
    std::map<size_t, size_t> unitAmount;
    for (const auto& size : OverallUnits.at(category)) {
      size_t amount = (size_t)std::ceil(weight * (double)size.second);
      size_t available = availableUnits[category][size.first];
      if (available > amount)
        amount = available;
      unitAmount[size.first] = amount;
      availableUnits[category][size.first] -= amount;
    }
    return unitAmount;
  }

  std::map<size_t, double> FormationCalculator::getCategoryWeightSum(const Formation& formation) {
    std::map<size_t, double> result;
    size_t category = formation.getUnitCategory();
    if (result.count(category) == 0)
      result[category] = 0;
    result[category] += formation.getUnitDistributionWeight();

    for (size_t i = 0; i < formation.getChildrenCount(); i++) {
      auto& child = formation.getChild(i);
      auto sub = getCategoryWeightSum(child);
      for (auto& keyvalue : sub) {
        if (result.count(keyvalue.first) == 0)
          result[keyvalue.first] = keyvalue.second;
        else
          result[keyvalue.first] += keyvalue.second;
      }
    }
    return result;
  }

  std::map<size_t, std::map<size_t, size_t>> FormationCalculator::getSizesPerCategory(const std::vector<Body>& units) {
    std::map<size_t, std::map<size_t, size_t>> result;
    for (auto& x : units) {
      if (result.count(x.category) == 0)
        result[x.category] = std::map<size_t, size_t>();
      if (result[x.category].count(x.size) == 0)
        result[x.category][x.size] = 0;
      result[x.category][x.size]++;
    }
    return result;
  }
}