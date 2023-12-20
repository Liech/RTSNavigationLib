#pragma once

#include <memory>
#include "FormationShape.h"

namespace RTSPathingLib {
  class FormationShapeFactory {
  public:
    static std::unique_ptr<FormationShape> make();
  };
}