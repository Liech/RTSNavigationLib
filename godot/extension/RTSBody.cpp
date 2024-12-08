#include "RTSBody.h"
#include <godot_cpp/core/class_db.hpp>

namespace godot
{
    void RTSBody::_bind_methods()
    {
        ClassDB::bind_method(D_METHOD("get_position"), &RTSBody::get_position);
        ClassDB::bind_method(D_METHOD("set_position", "val"), &RTSBody::set_position);
        ClassDB::bind_method(D_METHOD("get_category"), &RTSBody::get_category);
        ClassDB::bind_method(D_METHOD("set_category", "val"), &RTSBody::set_category);
        ClassDB::bind_method(D_METHOD("get_size"), &RTSBody::get_size);
        ClassDB::bind_method(D_METHOD("set_size", "val"), &RTSBody::set_size);
        ClassDB::bind_method(D_METHOD("get_id"), &RTSBody::get_id);
        ClassDB::bind_method(D_METHOD("set_id", "val"), &RTSBody::set_id);

        ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "position"), "set_position", "get_position");
        ADD_PROPERTY(PropertyInfo(Variant::INT, "category"), "set_category", "get_category");
        ADD_PROPERTY(PropertyInfo(Variant::INT, "size"), "set_size", "get_size");
        ADD_PROPERTY(PropertyInfo(Variant::INT, "id"), "set_id", "get_id");
    }

    RTSBody::RTSBody()
    {
        // Initialize any variables here.
    }

    RTSBody::~RTSBody()
    {
        // Add your cleanup here.
    }

    RTSNavigationLib::Body RTSBody::toBody() const
    {
        RTSNavigationLib::Body result;
        result.category = category;
        result.position = position;
        result.size     = size;
        result.id       = id;
        return result;
    }

    Vector2 RTSBody::get_position() const
    {
        return Vector2(position.x, position.y);
    }
    void RTSBody::set_position(const Vector2& v)
    {
        position = glm::dvec2(v.x, v.y);
    }
    int RTSBody::get_category() const
    {
        return category;
    }
    void RTSBody::set_category(int c)
    {
        category = c;
    }
    int RTSBody::get_size() const
    {
        return size;
    }
    void RTSBody::set_size(int v)
    {
        size = v;
    }
    int RTSBody::get_id() const
    {
        return id;
    }
    void RTSBody::set_id(int v)
    {
        id = v;
    }
}