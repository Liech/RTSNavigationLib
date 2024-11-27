#pragma once

#include <godot_cpp/classes/ref_counted.hpp>

namespace godot {

class RTSNavigation : public RefCounted {
	GDCLASS(RTSNavigation, RefCounted)

protected:
	static void _bind_methods();

public:
	RTSNavigation();
	~RTSNavigation();

	// Static method.
	static int test_static(int p_a, int p_b);
	static void test_static2();
};

}