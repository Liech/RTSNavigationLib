#include "RTSFormationShape.h"
#include <godot_cpp/core/class_db.hpp>

namespace godot
{
    void RTSFormationShape::_bind_methods()
    {
        BIND_ENUM_CONSTANT(PureX      );
        BIND_ENUM_CONSTANT(PureY      );
        BIND_ENUM_CONSTANT(Isotropic  );
        BIND_ENUM_CONSTANT(X75Y25     );
        BIND_ENUM_CONSTANT(X25Y75     );

        ClassDB::bind_method(D_METHOD("get_hollow"), &RTSFormationShape::get_hollow);
        ClassDB::bind_method(D_METHOD("set_hollow", "hollow"), &RTSFormationShape::set_hollow);
        ClassDB::bind_method(D_METHOD("get_base_size"), &RTSFormationShape::get_base_size);
        ClassDB::bind_method(D_METHOD("set_base_size", "base_size"), &RTSFormationShape::set_base_size);
        ClassDB::bind_method(D_METHOD("get_scaling_behavior"), &RTSFormationShape::get_scaling_behavior);
        ClassDB::bind_method(D_METHOD("set_scaling_behavior", "base_size"), &RTSFormationShape::set_scaling_behavior);

        ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "hollow"), "set_hollow", "get_hollow");
        ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "base_size"), "set_base_size", "get_base_size");
        ClassDB::add_property(get_class_static(),
                              PropertyInfo(Variant::INT, "scaling_behavior", PROPERTY_HINT_ENUM, "pure_x,pure_y,isotropic,X75_Y25,X25_Y75", PROPERTY_USAGE_DEFAULT),
                              "set_scaling_behavior",
                              "get_scaling_behavior");
    }
    
    RTSFormationShape::RTSFormationShape()
    {
        // Initialize any variables here.
    }

    RTSFormationShape::~RTSFormationShape()
    {
        // Add your cleanup here.
    }

    Vector2 RTSFormationShape::get_base_size() const
    {
        return Vector2(baseSize.x, baseSize.y);
    }
    void RTSFormationShape::set_base_size(const Vector2& x)
    {
        baseSize = glm::dvec2(x.x, x.y);
    }
    double RTSFormationShape::get_hollow() const
    {
        return hollow;
    }
    void RTSFormationShape::set_hollow(double val)
    {
        hollow = val;
    }
    RTSFormationShape::ScalingBehavior RTSFormationShape::get_scaling_behavior() const
    {
        return (RTSFormationShape::ScalingBehavior)scaling;
    }
    void RTSFormationShape::set_scaling_behavior(RTSFormationShape::ScalingBehavior s)
    {
        scaling = (RTSNavigationLib::ScalingBehavior)s;
    }

}