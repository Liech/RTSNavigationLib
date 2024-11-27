#include "RTSNavigation.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void RTSNavigation::_bind_methods() {

	ClassDB::bind_static_method("RTSNavigation", D_METHOD("test_static", "a", "b"), &RTSNavigation::test_static);
	ClassDB::bind_static_method("RTSNavigation", D_METHOD("test_static2"), &RTSNavigation::test_static2);
}

RTSNavigation::RTSNavigation() {
	// Initialize any variables here.
	time_passed = 0.0;
}

RTSNavigation::~RTSNavigation() {
	// Add your cleanup here.
}

int RTSNavigation::test_static(int p_a, int p_b) {
	return p_a + p_b;
}

void RTSNavigation::test_static2() {
	//UtilityFunctions::print("  void static");
}