#pragma once

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

namespace godot {
  class RTSFormation : public Resource {
    GDCLASS(RTSFormation, Resource)

  protected:
    static void _bind_methods();

  public:
    RTSFormation();
    ~RTSFormation();

    void set_category(const int cat);
    int get_category() const;
    void set_children(const TypedArray<RTSFormation>& cat);
    TypedArray<RTSFormation> get_children() const;
  private:
    int category = 0;
    TypedArray<RTSFormation> children;
  };
}