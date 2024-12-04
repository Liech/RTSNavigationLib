#pragma once

#include "RTSFormationShape.h"
#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <memory>

namespace godot
{
    class RTSFormation : public Resource
    {
        GDCLASS(RTSFormation, Resource)
      public:
        RTSFormation();
        virtual ~RTSFormation();

        enum PlacementBehavior
        {
            center_first_rts,
            outer_first_rts,
            distribute_evenly_rts
        };

      protected:
        static void _bind_methods();

      private:
        void                     set_placement_behavior(const PlacementBehavior cat);
        PlacementBehavior        get_placement_behavior() const;
        void                     set_unit_category(const int cat);
        int                      get_unit_category() const;
        void                     set_unit_distribution_weight(const float cat);
        float                    get_unit_distribution_weight() const;
        void                     set_rotation(const float cat);
        float                    get_rotation() const;
        void                     set_children(const TypedArray<RTSFormation>& cat);
        TypedArray<RTSFormation> get_children() const;
        bool                     get_rotate_with_interface() const;
        void                     set_rotate_with_interface(bool val);
        bool                     get_overwrite_width_with_interface_width() const;
        void                     set_overwrite_width_with_interface_width(bool val);
        int                      get_own_interface_point() const;
        void                     set_own_interface_point(int ptr);
        int                      get_parent_interface_point() const;
        void                     set_parent_interface_point(int ptr);
        Ref<RTSFormationShape>   get_shape() const;
        void                     set_shape(Ref<RTSFormationShape>);

        Ref<RTSFormationShape> shape                            = nullptr;
        int                    ownInterfacePoint                = 0;
        int                    parentInterfacePoint             = 0;
        bool                   overwriteWidthWithInterfaceWidth = false;
        bool                   rotateWithInterface              = false;
        float                  rotation                         = 0.0;
        int                    unitCategory                     = 0;
        float                  unitDistributionWeight           = 1.0;
        PlacementBehavior      placementBehavior                = PlacementBehavior::center_first_rts;

        TypedArray<RTSFormation> children;
    };
}

VARIANT_ENUM_CAST(godot::RTSFormation::PlacementBehavior);
