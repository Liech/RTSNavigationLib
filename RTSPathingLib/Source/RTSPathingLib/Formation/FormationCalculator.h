#pragma once

#include <map>
#include <vector>
#include <glm/glm.hpp>


namespace RTSPathingLib {
  struct Body;
  class Formation;

  class FormationCalculator {
  public:
    static std::vector<Body> calculate(const Formation&, const std::vector<Body>& units);

  private:
    static std::map<size_t, std::map<size_t, size_t>> getSizesPerCategory(const std::vector<Body>& units);
  };
}