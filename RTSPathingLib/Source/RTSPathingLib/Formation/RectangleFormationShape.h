#pragma once

#include "FormationShape.h"

class RectangleFormationShape : public FormationShape {
public:
  RectangleFormationShape();
  virtual ~RectangleFormationShape();

  void setScalingRatio(float v);
  float getScalingRatio() const;

private:
  float scalingRatio = 0.5f;
};