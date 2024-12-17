#include "RTSFormation.h"
#include <RTSNavigationLib/Formation/FormationCalculator.h>
#include <godot_cpp/core/class_db.hpp>

namespace godot
{
    void RTSFormation::_bind_methods()
    {
        BIND_ENUM_CONSTANT(center_first_rts);
        BIND_ENUM_CONSTANT(outer_first_rts);
        BIND_ENUM_CONSTANT(distribute_evenly_rts);

        ClassDB::bind_method(D_METHOD("get_unit_categories"), &RTSFormation::get_unit_categories);
        ClassDB::bind_method(D_METHOD("set_unit_categories", "categories"), &RTSFormation::set_unit_categories);
        ClassDB::bind_method(D_METHOD("get_children"), &RTSFormation::get_children);
        ClassDB::bind_method(D_METHOD("set_children", "children"), &RTSFormation::set_children);
        ClassDB::bind_method(D_METHOD("get_placement_behavior"), &RTSFormation::get_placement_behavior);
        ClassDB::bind_method(D_METHOD("set_placement_behavior", "placement_behavior"), &RTSFormation::set_placement_behavior);
        ClassDB::bind_method(D_METHOD("get_unit_distribution_weight"), &RTSFormation::get_unit_distribution_weight);
        ClassDB::bind_method(D_METHOD("set_unit_distribution_weight", "placement_behavior"), &RTSFormation::set_unit_distribution_weight);
        ClassDB::bind_method(D_METHOD("get_rotation"), &RTSFormation::get_rotation);
        ClassDB::bind_method(D_METHOD("set_rotation", "rotation"), &RTSFormation::set_rotation);

        ClassDB::bind_method(D_METHOD("get_rotate_with_interface"), &RTSFormation::get_rotate_with_interface);
        ClassDB::bind_method(D_METHOD("set_rotate_with_interface", "val"), &RTSFormation::set_rotate_with_interface);
        ClassDB::bind_method(D_METHOD("get_overwrite_width_with_interface_width"), &RTSFormation::get_overwrite_width_with_interface_width);
        ClassDB::bind_method(D_METHOD("set_overwrite_width_with_interface_width", "val"), &RTSFormation::set_overwrite_width_with_interface_width);
        ClassDB::bind_method(D_METHOD("get_own_interface_point"), &RTSFormation::get_own_interface_point);
        ClassDB::bind_method(D_METHOD("set_own_interface_point", "val"), &RTSFormation::set_own_interface_point);
        ClassDB::bind_method(D_METHOD("get_parent_interface_point"), &RTSFormation::get_parent_interface_point);
        ClassDB::bind_method(D_METHOD("set_parent_interface_point", "val"), &RTSFormation::set_parent_interface_point);
        ClassDB::bind_method(D_METHOD("get_shape"), &RTSFormation::get_shape);
        ClassDB::bind_method(D_METHOD("set_shape", "val"), &RTSFormation::set_shape);

        ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "categories"), "set_unit_categories", "get_unit_categories");
        ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "weight"), "set_unit_distribution_weight", "get_unit_distribution_weight");
        ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "rotation"), "set_rotation", "get_rotation");
        ADD_PROPERTY(PropertyInfo(Variant::BOOL, "rotate_with_interface"), "set_rotate_with_interface", "get_rotate_with_interface");
        ADD_PROPERTY(PropertyInfo(Variant::BOOL, "overwrite_width_with_interface_width"), "set_overwrite_width_with_interface_width", "get_overwrite_width_with_interface_width");
        ADD_PROPERTY(PropertyInfo(Variant::INT, "own_interface_point"), "set_own_interface_point", "get_own_interface_point");
        ADD_PROPERTY(PropertyInfo(Variant::INT, "parent_interface_point"), "set_parent_interface_point", "get_parent_interface_point");
        ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "shape", PROPERTY_HINT_RESOURCE_TYPE, "RTSFormationShape"), "set_shape", "get_shape");
        ClassDB::add_property(get_class_static(),
                              PropertyInfo(Variant::INT, "placement_behavior", PROPERTY_HINT_ENUM, "center_first,outer_first_rts,distribute_evenly_rts", PROPERTY_USAGE_DEFAULT),
                              "set_placement_behavior",
                              "get_placement_behavior");

        ClassDB::add_property("RTSFormation",
                              PropertyInfo(Variant::ARRAY, "children", PROPERTY_HINT_TYPE_STRING, String::num(Variant::OBJECT) + "/" + String::num(PROPERTY_HINT_RESOURCE_TYPE) + ":RTSFormation"),
                              "set_children",
                              "get_children");
        ClassDB::bind_method(D_METHOD("calculate", "bodies"), &RTSFormation::calculate);
        ClassDB::bind_method(D_METHOD("toJson"), &RTSFormation::toJSON);
    }

    RTSFormation::RTSFormation()
    {
        // Initialize any variables here.
    }

    RTSFormation::~RTSFormation()
    {
        // Add your cleanup here.
    }

    godot::String RTSFormation::toJSON() const
    {
        return godot::String(toFormation()->toJson().dump(2).c_str());
    }

    TypedArray<RTSBody> RTSFormation::calculate(const TypedArray<RTSBody>& pre_bodies) const
    {
        std::vector<RTSNavigationLib::WorldBody> bodies;
        for (size_t i = 0; i < pre_bodies.size(); i++)
            bodies.push_back(godot::Object::cast_to<RTSBody>(pre_bodies[i])->toBody());
        auto form = toFormation();

        auto places = RTSNavigationLib::FormationCalculator(*form, bodies).calculate();
        TypedArray<RTSBody> result;

        for (const auto& x : places)
        {
          
            Ref<RTSBody> place;
            place.instantiate();
            place->category = x.category;
            place->size     = x.size;
            place->position = x.position;
            result.push_back(place);
        }

        return result;
    }

    std::unique_ptr<RTSNavigationLib::Formation> RTSFormation::toFormation() const
    {
        auto result = std::make_unique<RTSNavigationLib::Formation>();
        result->setOwnInterfacePoint(ownInterfacePoint);
        result->setParentInterfacePoint(parentInterfacePoint);
        result->setOverwriteWidthWithInterfaceWidth(overwriteWidthWithInterfaceWidth);
        result->setRotateWithInterface(rotateWithInterface);
        result->setRotation(rotation);
        result->setUnitDistributionWeight(unitDistributionWeight);
        result->setPlacementBehavior((RTSNavigationLib::UnitPlacementBehavior)placementBehavior);
        result->setShape(shape->toShape());

        for (size_t i = 0; i < children.size(); i++)
        {
            result->addChild(std::move(godot::Object::cast_to<RTSFormation>(children[i]))->toFormation());
        }
        
        std::vector<size_t> cats;
        cats.reserve(unitCategories.size());
        for (size_t i = 0; i < unitCategories.size(); i++)
        {
            cats.push_back(unitCategories[i]);
        }
        result->setUnitCategories(cats);

        return std::move(result);
    }

    void RTSFormation::set_unit_categories(const TypedArray<int>& cat)
    {
        unitCategories = cat;
    }
    TypedArray<int> RTSFormation::get_unit_categories() const
    {
        return unitCategories;
    }
    void RTSFormation::set_children(const TypedArray<RTSFormation>& children_)
    {
        children = children_;
    }
    TypedArray<RTSFormation> RTSFormation::get_children() const
    {
        return children;
    }
    void RTSFormation::set_placement_behavior(const RTSFormation::PlacementBehavior b)
    {
        placementBehavior = b;
    }
    RTSFormation::PlacementBehavior RTSFormation::get_placement_behavior() const
    {
        return placementBehavior;
    }
    void RTSFormation::set_unit_distribution_weight(const float w)
    {
        unitDistributionWeight = w;
    }
    float RTSFormation::get_unit_distribution_weight() const
    {
        return unitDistributionWeight;
    }
    void RTSFormation::set_rotation(const float rot)
    {
        rotation = rot;
    }
    float RTSFormation::get_rotation() const
    {
        return rotation;
    }
    bool RTSFormation::get_rotate_with_interface() const
    {
        return rotateWithInterface;
    }
    void RTSFormation::set_rotate_with_interface(bool val)
    {
        rotateWithInterface = val;
    }
    bool RTSFormation::get_overwrite_width_with_interface_width() const
    {
        return overwriteWidthWithInterfaceWidth;
    }
    void RTSFormation::set_overwrite_width_with_interface_width(bool val)
    {
        overwriteWidthWithInterfaceWidth = val;
    }
    int RTSFormation::get_own_interface_point() const
    {
        return ownInterfacePoint;
    }
    void RTSFormation::set_own_interface_point(int ptr)
    {
        ownInterfacePoint = ptr;
    }
    int RTSFormation::get_parent_interface_point() const
    {
        return parentInterfacePoint;
    }
    void RTSFormation::set_parent_interface_point(int ptr)
    {
        parentInterfacePoint = ptr;
    }
    Ref<RTSFormationShape> RTSFormation::get_shape() const
    {
        return shape;
    }
    void RTSFormation::set_shape(Ref<RTSFormationShape> val)
    {
        shape = val;
    }
}