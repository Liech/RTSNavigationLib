#pragma once

#include <godot_cpp/classes/ref_counted.hpp>
#include "RTSBody.h"

namespace godot {

class RTSNavigation : public RefCounted {
	GDCLASS(RTSNavigation, RefCounted)

protected:
	static void _bind_methods();

public:
	RTSNavigation();
  virtual ~RTSNavigation();

	static TypedArray<int> usher(const TypedArray<RTSBody>& units, const TypedArray<RTSBody>& places);
};

}