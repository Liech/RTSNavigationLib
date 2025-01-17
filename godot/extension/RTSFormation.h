#pragma once

#include "RTSBody.h"
#include "RTSFormationShape.h"
#include <RTSNavigationLib/Formation/Formation.h>
#include <godot_cpp/classes/polygon2d.hpp>
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
            center_first_rts      = 0,
            outer_first_rts       = 1,
            distribute_evenly_rts = 2,
            front_first_rts       = 3,
            rear_first_rts        = 4
        };

      protected:
        static void _bind_methods();

      private:
        void                           set_placement_behavior(const PlacementBehavior cat);
        PlacementBehavior              get_placement_behavior() const;
        void                           set_cut_behavior(const PlacementBehavior cat);
        PlacementBehavior              get_cut_behavior() const;
        void                           set_unit_categories(const TypedArray<int>& cat);
        TypedArray<int>                get_unit_categories() const;
        void                           set_unit_distribution_weight(const float cat);
        float                          get_unit_distribution_weight() const;
        void                           set_rotation(const float cat);
        float                          get_rotation() const;
        void                           set_children(const TypedArray<RTSFormation>& cat);
        TypedArray<RTSFormation>       get_children() const;
        bool                           get_rotate_with_interface() const;
        void                           set_rotate_with_interface(bool val);
        bool                           get_overwrite_width_with_interface_width() const;
        void                           set_overwrite_width_with_interface_width(bool val);
        int                            get_own_interface_point() const;
        void                           set_own_interface_point(int ptr);
        int                            get_parent_interface_point() const;
        void                           set_parent_interface_point(int ptr);
        bool                           get_center_shift() const;
        void                           set_center_shift(bool active);
        bool                           get_remaining_unit_sink() const;
        void                           set_remaining_unit_sink(bool active);
        Ref<RTSFormationShape>         get_shape() const;
        void                           set_shape(Ref<RTSFormationShape>);
        TypedArray<RTSBody>            calculate(const TypedArray<RTSBody>&);
        TypedArray<PackedVector2Array> getResultShapes() const;
        TypedArray<PackedVector2Array> getDebugShapes() const;
        godot::String                  toJSON() const;

        std::unique_ptr<RTSNavigationLib::Formation> toFormation() const;

        Ref<RTSFormationShape> shape                            = nullptr;
        int                    ownInterfacePoint                = 0;
        int                    parentInterfacePoint             = 0;
        bool                   overwriteWidthWithInterfaceWidth = false;
        bool                   rotateWithInterface              = false;
        float                  rotation                         = 0.0;
        TypedArray<int>        unitCategories;
        float                  unitDistributionWeight = 1.0;
        PlacementBehavior      placementBehavior      = PlacementBehavior::center_first_rts;
        PlacementBehavior      cutBehavior            = PlacementBehavior::center_first_rts;
        bool                   centerShift            = false;
        bool                   remainingUnitsSink     = false;

        std::vector<std::vector<glm::dvec2>> allPolygons;
        std::vector<std::vector<glm::dvec2>> debugPolygons;

        TypedArray<RTSFormation> children;
    };
}

VARIANT_ENUM_CAST(godot::RTSFormation::PlacementBehavior);
