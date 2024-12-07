#include "RTSShapeTri.h"
#include <RTSNavigationLib/Formation/FormationShape/TriangleFormationShape.h>
#include <godot_cpp/core/class_db.hpp>

namespace godot
{
    void RTSShapeTri::_bind_methods() {}

    RTSShapeTri::RTSShapeTri()
    {
        // Initialize any variables here.
    }

    RTSShapeTri::~RTSShapeTri()
    {
        // Add your cleanup here.
    }
    std::unique_ptr<RTSNavigationLib::FormationShape> RTSShapeTri::toShape() const
    {
        auto result = std::make_unique<RTSNavigationLib::TriangleFormationShape>();
        result->setHollow(hollow);
        result->setBaseSize(baseSize);
        result->setScalingBehavior((RTSNavigationLib::ScalingBehavior)scaling);
        return result;
    }
}