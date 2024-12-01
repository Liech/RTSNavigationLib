#pragma once

#include "RTSFormationShape.h"

namespace godot {
  class RTSShapeCircle : public RTSFormationShape {
    GDCLASS(RTSShapeCircle, RTSFormationShape)

  protected:
    static void _bind_methods();

  public:
    RTSShapeCircle();
    ~RTSShapeCircle();

  };
}