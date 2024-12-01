#pragma once

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

namespace godot {
  class RTSFormation : public Resource {
    GDCLASS(RTSFormation, Resource)
  public:
    RTSFormation();
    ~RTSFormation();


    enum PlacementBehavior {
      center_first_rts, outer_first_rts, distribute_evenly_rts
    };

  protected:
    static void _bind_methods();

  private:
    void set_placement_behavior(const PlacementBehavior cat);
    PlacementBehavior get_placement_behavior() const;
    void set_category(const int cat);
    int get_category() const;
    void set_unit_distribution_weight(const float cat);
    float get_unit_distribution_weight() const;
    void set_rotation(const float cat);
    float get_rotation() const;
    void set_children(const TypedArray<RTSFormation>& cat);
    TypedArray<RTSFormation> get_children() const;


    PlacementBehavior placementBehavior = PlacementBehavior::center_first_rts;
    int category = 0;
    float unitDistributionWeight = 1.0;
    float rotation = 0.0;

    TypedArray<RTSFormation> children;
  };
}

VARIANT_ENUM_CAST(godot::RTSFormation::PlacementBehavior);
