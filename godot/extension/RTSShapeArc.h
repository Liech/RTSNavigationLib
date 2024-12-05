#pragma once

#include "RTSFormationShape.h"

namespace godot
{
    class RTSShapeArc : public RTSFormationShape
    {
        GDCLASS(RTSShapeArc, RTSFormationShape)

      protected:
        static void _bind_methods();

      public:
        RTSShapeArc();
        virtual ~RTSShapeArc();

        double get_arc_angle_radian() const;
        void   set_arc_angle_radian(double);

        double arcAngleRadian = 0.0;
    };
}