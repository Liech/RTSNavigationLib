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

    float scale = 1;
    bool bigEnough = false;
    std::vector<Body> result = formate(scale, current,overall,currentTransformation,formation, bigEnough);
   

    return result;
  }

  std::vector<Body> FormationCalculator::formate(float scale, std::map<size_t, std::map<size_t, size_t>>& current, const std::map<size_t, std::map<size_t, size_t>>& overall, glm::mat4& currentTransformation, const Formation& formation, bool& bigEnough) {
    auto unitsPlacedHere  = gatherUnits(formation, overall, current);
    auto formationSize    = getSizeSum(unitsPlacedHere);
    auto localTransform   = getLocalTransformation(formation, scale);
    currentTransformation = currentTransformation * localTransform;
    RectangleGrid<bool> grid = getGrid(formation, currentTransformation);


    std::vector<Body> placedUnits = placeUnits(grid, unitsPlacedHere, grid.offset, formation.getUnitCategory(), bigEnough);


    return placedUnits;
  }

  RectangleGrid<bool> FormationCalculator::getGrid(const Formation& formation, const glm::mat4& transformation) {
    auto polygon = formation.getShape().getPolygon();
    for (auto& x : polygon)
      x = glm::vec4(x, 0, 1) * transformation;

    auto       minMax    = getMinMax(polygon);
    glm::ivec2 dimension = (glm::ivec2)(minMax.second - minMax.first) + glm::ivec2(3, 3);
    glm::vec2  offset    = (glm::vec2)((glm::ivec2)(minMax.first)) - glm::vec2(2, 2);

    auto grid = RectangleGridVoxelizer::voxelize(polygon, dimension, offset);

    auto svgDebug = RectangleGridSvg::write(grid, 1);
    svg debug;
    debug.streak = polygon;
    debug.wrapAround = true;
    debug.color = "green";
    debug.thickness = 0.1;
    svgDebug.push_back(debug);
    svg::write("FormationCalculator.svg", svgDebug, glm::vec2(-5, -5), glm::vec2(10, 10));

    return grid;
  }

  std::vector<Body> FormationCalculator::placeUnits(const RectangleGrid<bool>& grid, const std::map<size_t, size_t>& units, const glm::vec2& offset, size_t category, bool& ok) {
    std::vector<Body> result;
    size_t currentSize = 1;
    long long unitsToPlace = (long long)units.at(currentSize);
    for (size_t i = 0; i < grid.data.size(); i++) {
      if (grid.data[i]) {
        glm::ivec2 pos = glm::ivec2(i % grid.dimension.x, (i / grid.dimension.x) % grid.dimension.y);
        Body sub;
        sub.category = category;
        sub.size = currentSize;
        sub.position = (glm::vec2)pos + offset;
        result.push_back(sub);
        unitsToPlace--;
      }      
    }
    if (unitsToPlace == 0)
      ok = true;

    return result;
  }

  std::pair<glm::vec2, glm::vec2> FormationCalculator::getMinMax(const std::vector<glm::vec2>& polygon) {
    glm::vec2 min = glm::vec2( std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
    glm::vec2 max = glm::vec2(-std::numeric_limits<float>::max(),-std::numeric_limits<float>::max());

    for (auto& x : polygon) {
      min.x = std::min(x.x, min.x);
      min.y = std::min(x.y, min.y);
      max.x = std::max(x.x, max.x);
      max.y = std::max(x.y, max.y);
    }

    return std::make_pair(min, max);
  }

  //rotation, parent transformation etc missing
  glm::mat4 FormationCalculator::getLocalTransformation(const Formation& formation, float scale) {
    FormationShape& shape = formation.getShape();
    glm::mat4 parentTransform = glm::mat4(1);

    glm::vec2 interfacePoint = shape.getInterfacePoint(formation.getOwnInterfacePoint());
    glm::mat4 result = glm::mat4(1);
    result = glm::translate(result, glm::vec3(interfacePoint * scale, 0));
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
    float weight = formation.getUnitDistributionWeight();
    std::map<size_t, size_t> unitAmount;
    for (const auto& size : OverallUnits.at(category)) {
      size_t amount = std::ceil(weight * size.second);
      size_t available = availableUnits[category][size.first];
      if (available > amount)
        amount = available;
      unitAmount[size.first] = amount;
      availableUnits[category][size.first] -= amount;
    }
    return unitAmount;
  }

  std::map<size_t, float> FormationCalculator::getCategoryWeightSum(const Formation& formation) {
    std::map<size_t, float> result;
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