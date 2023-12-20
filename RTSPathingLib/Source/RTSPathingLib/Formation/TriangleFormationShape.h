#pragma once

#include "FormationShape.h"

class TriangleFormationShape : public FormationShape {
public:
  TriangleFormationShape();
  virtual ~TriangleFormationShape();

private:
  int  layoutEdge     = 0; //-1 for centered
};