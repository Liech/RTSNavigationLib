#pragma once

#include <memory>
#include <nlohmann/json.hpp>

#include "FormationShape.h"

namespace RTSNavigationLib {
  class FormationShapeFactory {
  public:
    static std::unique_ptr<FormationShape> make(const nlohmann::json&);
  };
}