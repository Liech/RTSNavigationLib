#include "RTSFormation.h"
#include <godot_cpp/core/class_db.hpp>

namespace godot {
  void RTSFormation::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_category"), &RTSFormation::get_category);
    ClassDB::bind_method(D_METHOD("set_category", "category"), &RTSFormation::set_category);
    ClassDB::bind_method(D_METHOD("get_children"), &RTSFormation::get_children);
    ClassDB::bind_method(D_METHOD("set_children", "children"), &RTSFormation::set_children);

    ADD_PROPERTY(PropertyInfo(Variant::INT, "category"), "set_category", "get_category");
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
}