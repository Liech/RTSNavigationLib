#include "FormationCalculator.h"

#include <glm/ext/matrix_transform.hpp>

#include "Formation.h"
#include "Body.h"
#include "Formation/FormationShape/FormationShape.h"
#include "UnitPlacement.h"

#include "Util/Geometry2D.h"
#include "Util/svg.h"
#include "Util/RectangleGrid/RectangleGridVoxelizer.h"
#include "Util/RectangleGrid/RectangleGridSvg.h"

namespace RTSPathingLib {
  FormationCalculator::FormationCalculator(const Formation& formation, const std::vector<Body>& units) :
  rootFormation(formation), inputUnits(units)
  {
    overall = getSizesPerCategory(units);
  }

  std::vector<Body> FormationCalculator::calculate() {
    glm::dmat4 currentTransformation = glm::dmat4(1);
    currentUnits = overall;
    weightSumPerCategory = getCategoryWeightSum(rootFormation);

    glm::dvec2 parentCenter = glm::dvec2(0, 0);
    size_t     parentSize = 1;
    double     parentRotation = 0;
    double     parentInterfaceWidth = 0;
    std::vector<Body> result = recurse(parentCenter, parentSize, parentRotation, parentInterfaceWidth, rootFormation);

    return result;
  }

  std::vector<Body> FormationCalculator::recurse(const glm::dvec2& parentCenter, size_t parentSize, double parentRotation, double parentInterfaceWidth, const Formation& formation) {
    size_t scale             = 1;
    auto  unitsPlacedHere    = gatherUnits(formation);
    auto  formationSize      = getSizeSum(unitsPlacedHere);
    std::vector<Body> result;

    RectangleGrid<bool> grid;

    glm::dvec2 formationCenter = glm::dvec2(0, 0);

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
      glm::mat4 toFormationCenter = getLocalTransformation(formation, parentCenter, parentSize, parentRotation, parentInterfaceWidth ,scale);
      formationCenter = toFormationCenter * glm::dvec4(0, 0, 0, 1);

      std::vector<glm::dvec2> polygon;
      grid = getGrid(formation, toFormationCenter, polygon);
      auto placer = UnitPlacement(grid, unitsPlacedHere, formation.getUnitCategory());
      result = placer.place(allPlaced);
      grid = placer.getUsedPositions();
      lastpolygon = polygon;

      saveAsSvg(result, grid, polygon);
      if (allPlaced) {
        allGrids.push_back(grid);
        allPolygons.push_back(polygon);
        break;
      }
      scale ++;      
    }

    if (tries <= 0)
      return {};

    for (size_t i = 0; i < formation.getChildrenCount(); i++) {
      auto& child = formation.getChild(i);
      glm::dvec3 vectorScale = getScalingVector(formation, parentInterfaceWidth, parentSize);
      auto sub = recurse(formationCenter, scale, parentRotation, formation.getShape().getInterfaceWidth(child.getParentInterfacePoint(), vectorScale), child);
      result.insert(result.end(), sub.begin(), sub.end());
    }

    saveAsSvg(result, grid, lastpolygon);
    return result;
  }
  
  glm::dmat4 FormationCalculator::getLocalTransformation(const Formation& formation, const glm::dvec2& parentCenter, size_t parentScale, double& parentRotation, double parentparentInterfaceWidth, size_t scale) {
    FormationShape& shape = formation.getShape();

    glm::dvec2 parentInterfacePoint = glm::dvec2(0, 0);
    glm::dvec2 parentInterfaceNormal = glm::dvec2(0, 1);
    double parentInterfaceWidth = 1;
    if (formation.hasParent()) {
      glm::dvec3 vectorScale = getScalingVector(formation.getParent(), parentparentInterfaceWidth, parentScale);
      parentInterfacePoint = formation.getParent().getShape().getInterfacePoint(formation.getParentInterfacePoint());
      parentInterfacePoint = glm::dvec2(parentInterfacePoint.x * vectorScale.x, parentInterfacePoint.y * vectorScale.y);
      parentInterfaceNormal = formation.getParent().getShape().getInterfaceNormal(formation.getParentInterfacePoint());
      parentInterfaceWidth = formation.getParent().getShape().getInterfaceWidth(formation.getParentInterfacePoint(), vectorScale);
    }

    glm::dvec2 interfacePoint = -shape.getInterfacePoint(formation.getOwnInterfacePoint());
    glm::dmat4 result = glm::dmat4(1);

    glm::dvec3 vectorScale = getScalingVector(formation, parentInterfaceWidth, scale);

    double rotation = formation.getRotation() + parentRotation;
    if (formation.getRotateWithInterface()) {
      double angle = Geometry2D::getAngle(glm::dvec2(0,1), parentInterfaceNormal);
      rotation = parentRotation + angle;
    }

    result = glm::translate(result, glm::dvec3(parentCenter, 0));
    result = glm::translate(result, glm::dvec3(parentInterfacePoint, 0));
    result = glm::rotate(result, rotation, glm::dvec3(0, 0, 1));
    result = glm::scale(result, vectorScale);
    result = glm::translate(result, glm::dvec3(interfacePoint, 0));
    return result;
  }
  
  void FormationCalculator::saveAsSvg(const std::vector<Body>& bodies, const RectangleGrid<bool>& grid,const std::vector<glm::dvec2>& currentPolygon) {
    if (!saveSVG)
      return;
    std::vector<std::string> colors = { "red", "green", "blue", "yellow", "grey", "lime", "navy", "aqua" };

    std::vector<svg> svgDebug = {};// RectangleGridSvg::write(grid, 1);

    for (auto& x : allPolygons) {
      svg debug;
      debug.streak = x;
      debug.wrapAround = true;
      debug.color = "blue";
      debug.thickness = 0.1;
      svgDebug.push_back(debug);
    }
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

  RectangleGrid<bool> FormationCalculator::getGrid(const Formation& formation, const glm::dmat4& transformation, std::vector<glm::dvec2>& polygon) {
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


  glm::dvec3 FormationCalculator::getScalingVector(const Formation& formation, double parentInterfaceWidth, size_t scale) {
    glm::dvec3 result;
    auto behavior = formation.getShape().getScalingBehavior();

    switch (behavior) {
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
      //first scale only x and than both, this hopefully allows more subtle formation grow
      bool   xScalesFirst = scale % 2 == 0;
      size_t translatedScale = 1 + (scale - 1) / 2;
      result = glm::dvec3(translatedScale + (xScalesFirst ? 1 : 0), translatedScale, 1);
      break;
    }

    if (formation.getOverwriteWidthWithInterfaceWidth()) {
      double base = formation.getShape().getBaseSize().x;
      result = glm::dvec3(parentInterfaceWidth / base, scale, 1);
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

  std::map<size_t, size_t> FormationCalculator::gatherUnits(const Formation& formation) {
    size_t category = formation.getUnitCategory();
    double weight = formation.getUnitDistributionWeight() / weightSumPerCategory[category];
    std::map<size_t, size_t> unitAmount;
    for (const auto& size : overall.at(category)) {
      size_t amount = (size_t)std::ceil(weight * (double)size.second);
      size_t available = currentUnits[category][size.first];
      if (amount > available)
        amount = available;
      unitAmount[size.first] = amount;
      currentUnits[category][size.first] -= amount;
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