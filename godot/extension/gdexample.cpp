#include "gdexample.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void GDExample::_bind_methods() {

	ClassDB::bind_static_method("GDExample", D_METHOD("test_static", "a", "b"), &GDExample::test_static);
	ClassDB::bind_static_method("GDExample", D_METHOD("test_static2"), &GDExample::test_static2);
}

GDExample::GDExample() {
	// Initialize any variables here.
	time_passed = 0.0;
}

GDExample::~GDExample() {
	// Add your cleanup here.
}

void GDExample::_process(double delta) {
	time_passed += delta;

	Vector2 new_position = Vector2(10.0 + (10.0 * sin(time_passed * 2.0)), 10.0 + (10.0 * cos(time_passed * 1.5)));

	set_position(new_position);
}

int GDExample::test_static(int p_a, int p_b) {
	return p_a + p_b;
}

void GDExample::test_static2() {
	//UtilityFunctions::print("  void static");
}