#pragma once

#include <glm/glm.hpp>
#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include "RTSNavigationLib/Formation/FormationShape/ScalingBehavior.h"

namespace godot
{
    class RTSFormationShape : public Resource
    {
        GDCLASS(RTSFormationShape, Resource)

      protected:
        static void _bind_methods();

      public:
        RTSFormationShape();
        virtual ~RTSFormationShape();

        enum ScalingBehavior
        {
            PureX     = 0,
            PureY     = 1,
            Isotropic = 2,
            X75Y25    = 3,
            X25Y75    = 4 
        };

        Vector2         get_base_size() const;
        void            set_base_size(const Vector2&);
        double          get_hollow() const;
        void            set_hollow(double);
        ScalingBehavior get_scaling_behavior() const;
        void            set_scaling_behavior(ScalingBehavior);

      private:
        RTSNavigationLib::ScalingBehavior scaling  = RTSNavigationLib::ScalingBehavior::Isotropic;
        glm::dvec2                        baseSize = glm::dvec2(1, 1);
        double                            hollow   = 0.0;
    };
}

VARIANT_ENUM_CAST(godot::RTSFormationShape::ScalingBehavior);