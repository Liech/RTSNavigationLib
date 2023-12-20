#pragma once

#include "FormationShape.h"

class ArcFormationShape : public FormationShape {
public:
  ArcFormationShape();
  virtual ~ArcFormationShape();

private:
  float layoutAngle    = 0.0f;
  float arcAngleRadian = 0.0f;
};