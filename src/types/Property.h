#pragma once

#include <any>
#include <unordered_map>
#include <unordered_set>

#include "ExceptionError.h"
#include "Property_internal.h"
#include "VectorVelocity.h"
#include "Point.h"
#include "Angel.h"
#include "VelocityRotate.h"

namespace otg {

constexpr PropertyKey PropertyKeyPosition = "Position";
constexpr PropertyKey PropertyKeyVelocity = "Velocity";
constexpr PropertyKey PropertyKeyHealth = "Health";
constexpr PropertyKey PropertyKeyFuel = "Fuel";
constexpr PropertyKey PropertyKeyAmmo = "Ammo";
constexpr PropertyKey PropertyKeyDirection = "Direction";
constexpr PropertyKey PropertyKeyVelocityRotate = "VelocityRotate";

SPECIFY_PROPERTY_TYPE(PropertyKeyPosition, Point, PositionProperty)
SPECIFY_PROPERTY_TYPE(PropertyKeyVelocity, VectorVelocity, VelocityProperty)
SPECIFY_PROPERTY_TYPE(PropertyKeyHealth, int, HealthProperty)
SPECIFY_PROPERTY_TYPE(PropertyKeyFuel, int, FuelProperty)
SPECIFY_PROPERTY_TYPE(PropertyKeyAmmo, int, AmmoProperty)
SPECIFY_PROPERTY_TYPE(PropertyKeyDirection, Angel, DirectionProperty)
SPECIFY_PROPERTY_TYPE(PropertyKeyVelocityRotate, VelocityRotate, VelocityRotateProperty)

}  // namespace otg