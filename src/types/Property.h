#pragma once

#include <optional>
#include <unordered_map>
#include <any>

#include "Property_internal.h"
#include "Vector.h"

namespace otg {

using PropertyValue = std::any;
using PropertyValueOpt = std::optional<PropertyValue>;
using PropertyMap = std::unordered_map<PropertyKey,PropertyValue>;

constexpr PropertyKey PropertyKeyPosition = "Position";
constexpr PropertyKey PropertyKeyVelocity = "Velocity";
constexpr PropertyKey PropertyKeyHealth = "Health";
constexpr PropertyKey PropertyKeyFuel = "Fuel";
constexpr PropertyKey PropertyKeyAmmo = "Ammo";
constexpr PropertyKey PropertyKeyDirection = "Direction";
constexpr PropertyKey PropertyKeyVelocityRotate = "VelocityRotate";

SPECIFY_PROPERTY_TYPE(PropertyKeyPosition,otg::Vector,PositionProperty)
SPECIFY_PROPERTY_TYPE(PropertyKeyVelocity,otg::Vector,VelocityProperty)
SPECIFY_PROPERTY_TYPE(PropertyKeyHealth,int,HealthProperty)
SPECIFY_PROPERTY_TYPE(PropertyKeyFuel,int,FuelProperty)
SPECIFY_PROPERTY_TYPE(PropertyKeyAmmo,int,AmmoProperty)
SPECIFY_PROPERTY_TYPE(PropertyKeyDirection,otg::Vector,DirectionProperty)
SPECIFY_PROPERTY_TYPE(PropertyKeyVelocityRotate,otg::Vector,VelocityRotateProperty)

}