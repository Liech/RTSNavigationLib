#include "RTSShapeArc.h"
#include <godot_cpp/core/class_db.hpp>
#include <RTSNavigationLib/Formation/FormationShape/ArcFormationShape.h>

namespace godot
{
    void RTSShapeArc::_bind_methods()
    {
        ClassDB::bind_method(D_METHOD("get_arc_angle_radian"), &RTSShapeArc::get_arc_angle_radian);
        ClassDB::bind_method(D_METHOD("set_arc_angle_radian", "arc_angle_radian"), &RTSShapeArc::set_arc_angle_radian);

        ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "arc_angle_radian"), "set_arc_angle_radian", "get_arc_angle_radian");
    }

    RTSShapeArc::RTSShapeArc()
    {
        // Initialize any variables here.
    }

    RTSShapeArc::~RTSShapeArc()
    {
        // Add your cleanup here.
    }
    
    double RTSShapeArc::get_arc_angle_radian() const
    {
        return arcAngleRadian;
    }

    void RTSShapeArc::set_arc_angle_radian(double val)
    {
        arcAngleRadian = val;
    }

    std::unique_ptr<RTSNavigationLib::FormationShape> RTSShapeArc::toShape() const
    {
        auto result = std::make_unique<RTSNavigationLib::ArcFormationShape>();
        result->setHollow(hollow);
        result->setBaseSize(baseSize);
        result->setScalingBehavior((RTSNavigationLib::ScalingBehavior)scaling);
        result->setArcAngle(arcAngleRadian);
        return result;
    }
}