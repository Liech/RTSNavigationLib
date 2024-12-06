#pragma once

#include <glm/glm.hpp>
#include <godot_cpp/classes/resource.hpp>
#include <RTSNavigationLib/Body.h>

namespace godot
{
    class RTSBody : public Resource
    {
        GDCLASS(RTSBody, Resource)

      protected:
        static void _bind_methods();

      public:
        RTSBody();
        virtual ~RTSBody();

        RTSNavigationLib::Body toBody() const;

        Vector2 get_position() const;
        void    set_position(const Vector2&);
        int     get_category() const;
        void    set_category(int);
        int     get_size() const;
        void    set_size(int);

        glm::dvec2 position = glm::dvec2(0,0);
        int        category = 0;
        int        size     = 0;
    };
}