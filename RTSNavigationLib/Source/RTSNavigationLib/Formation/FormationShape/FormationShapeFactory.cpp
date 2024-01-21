#include "FormationShapeFactory.h"

#include "RectangleFormationShape.h"
#include "TriangleFormationShape.h"
#include "ArcFormationShape.h"

namespace RTSNavigationLib {
  std::unique_ptr<FormationShape> FormationShapeFactory::make(const nlohmann::json& input) {
    std::unique_ptr<FormationShape> result = nullptr;
    if (input["Type"] == "Rectangle") {
      std::unique_ptr<RectangleFormationShape> shape = std::make_unique<RectangleFormationShape>();
      shape->fromJson(input);
      return std::move(shape);
    }
    if (input["Type"] == "Triangle") {
      std::unique_ptr<TriangleFormationShape> shape = std::make_unique<TriangleFormationShape>();
      shape->fromJson(input);
      return std::move(shape);
    }
    if (input["Type"] == "Arc") {
      std::unique_ptr<ArcFormationShape> shape = std::make_unique<ArcFormationShape>();
      shape->fromJson(input);
      return std::move(shape);
    }
    return result;
  }
}