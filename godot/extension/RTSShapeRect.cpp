#include "RTSShapeRect.h"
#include <godot_cpp/core/class_db.hpp>
#include <RTSNavigationLib/Formation/FormationShape/RectangleFormationShape.h>

namespace godot {
  void RTSShapeRect::_bind_methods() {


  }

  RTSShapeRect::RTSShapeRect() {
    // Initialize any variables here.
  }

  RTSShapeRect::~RTSShapeRect() {
    // Add your cleanup here.
  }
  std::unique_ptr<RTSNavigationLib::FormationShape> RTSShapeRect::toShape() const
  {
      auto result = std::make_unique<RTSNavigationLib::RectangleFormationShape>();
      result->setHollow(hollow);
      result->setBaseSize(baseSize);
      result->setScalingBehavior((RTSNavigationLib::ScalingBehavior)scaling);
      return result;
  }
}