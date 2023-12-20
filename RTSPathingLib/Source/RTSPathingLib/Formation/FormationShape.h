#pragma once

#include <vector>
#include <glm/glm.hpp>

class FormationShape {
public:
  FormationShape();
  virtual ~FormationShape();

  virtual std::vector<glm::vec2> getPolygon() const;
};