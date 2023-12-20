#pragma once

#include <vector>
#include <glm/glm.hpp>


namespace RTSPathingLib {
  struct Body;
  class Formation;

  class FormationCalculator {
  public:
    static std::vector<Body> calculate(const Formation&, const std::vector<Body>& units);
  };
}