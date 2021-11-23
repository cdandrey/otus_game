#pragma once

#include <any>
#include <optional>
#include <unordered_map>

#include "Property_internal.h"
#include "Vector.h"

namespace otg {

using PropertyValueOpt = std::optional<PropertyValue>;
using PropertyMap = std::unordered_map<PropertyKey, PropertyValue>;
using PropertyResultGet = tl::expected<PropertyValue, PropertyError>;
using PropertyResultSet = tl::expected<std::true_type, PropertyError>;

constexpr PropertyKey PropertyKeyPosition = "Position";
constexpr PropertyKey PropertyKeyVelocity = "Velocity";
constexpr PropertyKey PropertyKeyHealth = "Health";
constexpr PropertyKey PropertyKeyFuel = "Fuel";
constexpr PropertyKey PropertyKeyAmmo = "Ammo";
constexpr PropertyKey PropertyKeyDirection = "Direction";
constexpr PropertyKey PropertyKeyVelocityRotate = "VelocityRotate";

SPECIFY_PROPERTY_TYPE(PropertyKeyPosition, Vector, PositionProperty)
SPECIFY_PROPERTY_TYPE(PropertyKeyVelocity, Vector, VelocityProperty)
SPECIFY_PROPERTY_TYPE(PropertyKeyHealth, int, HealthProperty)
SPECIFY_PROPERTY_TYPE(PropertyKeyFuel, int, FuelProperty)
SPECIFY_PROPERTY_TYPE(PropertyKeyAmmo, int, AmmoProperty)
SPECIFY_PROPERTY_TYPE(PropertyKeyDirection, Vector, DirectionProperty)
SPECIFY_PROPERTY_TYPE(PropertyKeyVelocityRotate, Vector, VelocityRotateProperty)

}  // namespace otg