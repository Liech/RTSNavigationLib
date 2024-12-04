#pragma once

#include <godot_cpp/classes/ref_counted.hpp>

namespace godot {

class RTSNavigation : public RefCounted {
	GDCLASS(RTSNavigation, RefCounted)

protected:
	static void _bind_methods();

public:
	RTSNavigation();
  virtual ~RTSNavigation();

	// Static method.
	static int test_static(int p_a, int p_b);
	static TypedArray<int> usher(const TypedArray<Vector2>& units, const TypedArray<Vector2>& places);
};

}