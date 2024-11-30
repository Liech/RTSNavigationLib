#include "RTSNavigation.h"
#include <godot_cpp/core/class_db.hpp>

#include <RTSNavigationLib/Usher/Usher.h>
#include "RTSNavigationLib/Body.h"
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void RTSNavigation::_bind_methods() {

  ClassDB::bind_static_method("RTSNavigation", D_METHOD("test_static", "a", "b"), &RTSNavigation::test_static);
  ClassDB::bind_static_method("RTSNavigation", D_METHOD("usher", "units", "places"), &RTSNavigation::usher);
}

RTSNavigation::RTSNavigation() {
  // Initialize any variables here.
}

RTSNavigation::~RTSNavigation() {
  // Add your cleanup here.
}

int RTSNavigation::test_static(int p_a, int p_b) {
  return p_a + p_b + 1;
}

TypedArray<int> RTSNavigation::usher(const TypedArray<Vector2>& units, const TypedArray<Vector2>& places) {
  TypedArray<int> result;
  std::vector<RTSNavigationLib::Body> unitsB;
  std::vector<RTSNavigationLib::Body> placesB;
  if (units.size() != places.size()) {
    return result;
  }
  for (size_t i = 0; i < units.size(); i++)
  {
    auto vec = units[i].operator godot::Vector2();
    unitsB.push_back(RTSNavigationLib::Body(glm::dvec2(vec.x, vec.y), 0, 1));
  }
  for (size_t i = 0; i < units.size(); i++)
  {
    auto vec = places[i].operator godot::Vector2();
    placesB.push_back(RTSNavigationLib::Body(glm::dvec2(vec.x, vec.y), 0, 1));
  }
  auto tickets = RTSNavigationLib::Usher::assignPlaces(unitsB, placesB);

  for (size_t i = 0; i < units.size(); i++)
  {
    result.push_back(tickets[i]);
  }
  return result;
}