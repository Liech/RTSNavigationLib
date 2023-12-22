#include "FormationCalculator.h"

#include <glm/ext/matrix_transform.hpp>

#include "Formation.h"
#include "Body.h"
#include "Formation/FormationShape/FormationShape.h"

#include "Util/svg.h"
#include "Util/RectangleGrid/RectangleGridVoxelizer.h"
#include "Util/RectangleGrid/RectangleGridSvg.h"

namespace RTSPathingLib {
  std::vector<Body> FormationCalculator::calculate(const Formation& formation, const std::vector<Body>& units) {
    glm::mat4 currentTransformation = glm::mat4(1);
    auto overall = getSizesPerCategory(units);
    auto current = overall;

    bool bigEnough = false;
    std::vector<Body> result = formate(current,overall,currentTransformation,formation, bigEnough);
   

    return result;
  }

  std::vector<Body> FormationCalculator::formate(std::map<size_t, std::map<size_t, size_t>>& current, const std::map<size_t, std::map<size_t, size_t>>& overall, glm::mat4& currentTransformation, const Formation& formation, bool& bigEnough) {
    size_t scale              = 1;
    auto  unitsPlacedHere    = gatherUnits(formation, overall, current);
    auto  formationSize      = getSizeSum(unitsPlacedHere);
    std::vector<Body> result;

    long long lastPlaced = -1;
    bool allPlaced = false;
    while (!allPlaced && lastPlaced != result.size()) {
      lastPlaced = result.size();
      auto  localTransform = getLocalTransformation(formation, scale);
      currentTransformation = localTransform;
      RectangleGrid<bool> grid = getGrid(formation, currentTransformation);
      result = placeUnits(grid, unitsPlacedHere, grid.offset, formation.getUnitCategory(), allPlaced);
      scale ++;
    }

    bigEnough = true;
    return result;
  }

  RectangleGrid<bool> FormationCalculator::getGrid(const Formation& formation, const glm::mat4& transformation) {
    auto polygon = formation.getShape().getPolygon();
    for (auto& x : polygon)
      x = glm::vec4(x, 0, 1) * transformation;

    auto       minMax    = getMinMax(polygon);
    glm::ivec2 dimension = (glm::ivec2)(minMax.second - minMax.first) + glm::ivec2(2, 2);
    glm::dvec2  offset    = (glm::dvec2)((glm::ivec2)(minMax.first+(minMax.second - minMax.first)/2.0)) - ((glm::dvec2)dimension)/2.0;

    auto grid = RectangleGridVoxelizer::voxelize(polygon, dimension, offset);

    auto svgDebug = RectangleGridSvg::write(grid, 1);
    svg debug;
    debug.streak = polygon;
    debug.wrapAround = true;
    debug.color = "green";
    debug.thickness = 0.1;
    svgDebug.push_back(debug);
    svg::write("FormationCalculator.svg", svgDebug, glm::dvec2(-5, -5), glm::dvec2(10, 10));

    return grid;
  }

  std::vector<Body> FormationCalculator::placeUnits(const RectangleGrid<bool>& grid, const std::map<size_t, size_t>& units, const glm::dvec2& offset, size_t category, bool& allPlaced) {
    std::vector<Body> result;
    size_t currentSize = 1;
    long long unitsToPlace = (long long)units.at(currentSize);
    for (size_t i = 0; i < grid.data.size() && unitsToPlace>0; i++) {
      if (grid.data[i]) {
        glm::ivec2 pos = glm::ivec2(i % grid.dimension.x, (i / grid.dimension.x) % grid.dimension.y);
        Body sub;
        sub.category = category;
        sub.size = currentSize;
        sub.position = (glm::dvec2)pos + offset + glm::dvec2(0.5,0.5);
        result.push_back(sub);
        unitsToPlace--;
      }      
    }
    if (unitsToPlace <= 0)
      allPlaced = true;

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
  glm::mat4 FormationCalculator::getLocalTransformation(const Formation& formation, size_t scale) {
    FormationShape& shape = formation.getShape();
    glm::mat4 parentTransform = glm::mat4(1);

    glm::dvec2 interfacePoint = shape.getInterfacePoint(formation.getOwnInterfacePoint());
    glm::mat4 result = glm::mat4(1);

    //first scale only x and than both, this hopefully allows more subtle formation grow
    bool   xScalesFirst = scale % 2 == 0;
    size_t translatedScale = 1 + (scale-1) / 2;
    glm::vec3 vectorScale = glm::vec3(translatedScale + (xScalesFirst?1:0), translatedScale,1);
    
    result = glm::scale(result, vectorScale);
    result = glm::translate(result, glm::vec3(interfacePoint.x,interfacePoint.y, 0));
    result *= parentTransform;
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
      size_t amount = std::ceil(weight * (double)size.second);
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