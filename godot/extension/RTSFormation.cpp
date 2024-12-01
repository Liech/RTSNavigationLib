#include "RTSFormation.h"
#include <godot_cpp/core/class_db.hpp>

namespace godot {
  void RTSFormation::_bind_methods() {
    BIND_ENUM_CONSTANT(center_first_rts);
    BIND_ENUM_CONSTANT(outer_first_rts);
    BIND_ENUM_CONSTANT(distribute_evenly_rts);

    ClassDB::bind_method(D_METHOD("get_category"), &RTSFormation::get_category);
    ClassDB::bind_method(D_METHOD("set_category", "category"), &RTSFormation::set_category);
    ClassDB::bind_method(D_METHOD("get_children"), &RTSFormation::get_children);
    ClassDB::bind_method(D_METHOD("set_children", "children"), &RTSFormation::set_children);
    ClassDB::bind_method(D_METHOD("get_placement_behavior"), &RTSFormation::get_placement_behavior);
    ClassDB::bind_method(D_METHOD("set_placement_behavior", "placement_behavior"), &RTSFormation::set_placement_behavior);
    ClassDB::bind_method(D_METHOD("get_unit_distribution_weight"), &RTSFormation::get_unit_distribution_weight);
    ClassDB::bind_method(D_METHOD("set_unit_distribution_weight", "placement_behavior"), &RTSFormation::set_unit_distribution_weight);
    ClassDB::bind_method(D_METHOD("get_rotation"), &RTSFormation::get_rotation);
    ClassDB::bind_method(D_METHOD("set_rotation", "rotation"), &RTSFormation::set_rotation);

    ADD_PROPERTY(PropertyInfo(Variant::INT, "category"), "set_category", "get_category");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "weight"), "set_unit_distribution_weight", "get_unit_distribution_weight");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "rotation"), "set_rotation", "get_rotation");
    ClassDB::add_property(get_class_static(), PropertyInfo(Variant::INT, "placement_behavior", PROPERTY_HINT_ENUM, "center_first,outer_first_rts,distribute_evenly_rts", PROPERTY_USAGE_DEFAULT), "set_placement_behavior", "get_placement_behavior");

    ClassDB::add_property("RTSFormation", PropertyInfo(
      Variant::ARRAY, 
      "children",
      PROPERTY_HINT_TYPE_STRING,
      String::num(Variant::OBJECT) + "/" + String::num(PROPERTY_HINT_RESOURCE_TYPE) + ":RTSFormation"
    ), "set_children", "get_children");



  
  }

  RTSFormation::RTSFormation() {
    // Initialize any variables here.
  }

  RTSFormation::~RTSFormation() {
    // Add your cleanup here.
  }

  void RTSFormation::set_category(const int cat) { category = cat; }
  int RTSFormation::get_category() const { return category; }
  void RTSFormation::set_children(const TypedArray<RTSFormation>& children_) { children = children_; }
  TypedArray<RTSFormation> RTSFormation::get_children() const { return children; }
  void RTSFormation::set_placement_behavior(const RTSFormation::PlacementBehavior b) { placementBehavior = b; }
  RTSFormation::PlacementBehavior RTSFormation::get_placement_behavior() const { return placementBehavior; }
  void RTSFormation::set_unit_distribution_weight(const float w) { unitDistributionWeight = w; }
  float RTSFormation::get_unit_distribution_weight() const { return unitDistributionWeight; }
  void RTSFormation::set_rotation(const float rot) { rotation = rot; }
  float RTSFormation::get_rotation() const { return rotation; }
}