#pragma once

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

namespace godot {
  class RTSFormationShape : public Resource {
    GDCLASS(RTSFormationShape, Resource)

  protected:
    static void _bind_methods();

  public:
    RTSFormationShape();
    virtual ~RTSFormationShape();

  };
}