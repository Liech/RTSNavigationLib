#pragma once

#include <memory>
#include "FormationShape.h"

class FormationShapeFactory {
public:
  static std::unique_ptr<FormationShape> make();
};