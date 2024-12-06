#pragma once

#include "RTSFormationShape.h"

namespace godot {
    class RTSShapeTri : public RTSFormationShape
    {
        GDCLASS(RTSShapeTri, RTSFormationShape)

  protected:
    static void _bind_methods();

  public:
    RTSShapeTri();
    virtual ~RTSShapeTri();

    virtual std::unique_ptr<RTSNavigationLib::FormationShape> toShape() const override;
  };
}