#include "RTSNavigation.h"
#include <godot_cpp/core/class_db.hpp>

#include "RTSNavigationLib/Body.h"
#include <RTSNavigationLib/Usher/Usher.h>
#include <godot_cpp/variant/utility_functions.hpp>

namespace godot
{
    void RTSNavigation::_bind_methods()
    {

        ClassDB::bind_static_method("RTSNavigation", D_METHOD("usher", "units", "places"), &RTSNavigation::usher);
    }

    RTSNavigation::RTSNavigation()
    {
        // Initialize any variables here.
    }

    RTSNavigation::~RTSNavigation()
    {
        // Add your cleanup here.
    }

    TypedArray<int> RTSNavigation::usher(const TypedArray<RTSBody>& units, const TypedArray<RTSBody>& places)
    {
        TypedArray<int>                          result;
        std::vector<RTSNavigationLib::WorldBody> unitsB;
        std::vector<RTSNavigationLib::WorldBody> placesB;
        if (units.size() != places.size())
        {
            return result;
        }
        for (size_t i = 0; i < units.size(); i++)
        {
            auto vec = godot::Object::cast_to<RTSBody>(units[i]);
            unitsB.push_back(vec->toBody());
        }
        for (size_t i = 0; i < units.size(); i++)
        {
            auto vec = godot::Object::cast_to<RTSBody>(places[i]);
            placesB.push_back(vec->toBody());
        }
        auto tickets = RTSNavigationLib::Usher::assignPlaces(unitsB, placesB);

        for (size_t i = 0; i < units.size(); i++)
        {
            result.push_back(tickets[i]);
        }
        return result;
    }
}