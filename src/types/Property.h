#pragma once

#include <optional>
#include <unordered_map>
#include <any>

#include "Property_internal.h"
#include "Vector.h"

namespace otg {

enum class PropertyKey
{
    Position,
    Velocity,
    Health,
    Fuel,
    Ammo,
    Direction,
    VelocityRotate
};

SPECIFY_PROPERTY_TYPE(Position,otg::Vector)
SPECIFY_PROPERTY_TYPE(Velocity,otg::Vector)
SPECIFY_PROPERTY_TYPE(Health,int)
SPECIFY_PROPERTY_TYPE(Fuel,int)
SPECIFY_PROPERTY_TYPE(Ammo,int)
SPECIFY_PROPERTY_TYPE(Direction,otg::Vector)
SPECIFY_PROPERTY_TYPE(VelocityRotate,otg::Vector)

using PropertyValue = std::any;
using PropertyValueOpt = std::optional<PropertyValue>;
using PropertyMap = std::unordered_map<PropertyKey,PropertyValue>;

}