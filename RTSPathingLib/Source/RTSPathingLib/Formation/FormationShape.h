#pragma once

#include <vector>
#include <glm/glm.hpp>

class FormationShape {
public:
  FormationShape();
  virtual ~FormationShape();

  virtual std::vector<glm::vec2> getPolygon() const;

  float getAngle() const;
  void  setAngle(float angle);
  virtual float getInterfaceWidth() const;
  void setLayoutCentered(bool v);
  bool getLayoutCentered() const;

private:
  float angle = 0;
  bool layoutCentered = false;
};