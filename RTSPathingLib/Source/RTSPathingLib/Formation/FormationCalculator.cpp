#include "FormationCalculator.h"

#include <glm/ext/matrix_transform.hpp>

#include "Formation.h"
#include "Body.h"
#include "Formation/FormationShape/FormationShape.h"

namespace RTSPathingLib {
  std::vector<Body> FormationCalculator::calculate(const Formation& formation, const std::vector<Body>& units) {
    glm::mat4 currentTransformation = glm::mat4(1);
    auto overall = getSizesPerCategory(units);
    auto current = overall;
    auto maxWeights = getCategoryWeightSum(formation);

    float scale = 1;
    auto unitsPlacedHere  = gatherUnits(formation, overall, current);
    auto formationSize    = getSizeSum(unitsPlacedHere);
    auto localTransform   = getLocalTransformation(formation, scale);
    currentTransformation = currentTransformation * localTransform;
    //create polygon
    //create grid
    //voxelize
    //count if it fits
    //repeat until fits

    return units;
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