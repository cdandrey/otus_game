#include "AdapterRotable.h"

#include <variant>

namespace otg {

AdapterRotable::AdapterRotable(const AbstractObjectPtr& object)
    : AbstractAdapter{ object }
{
}

Result<DirectionProperty::type> AdapterRotable::getDirection() const
{
    const auto onGetDirection = [](const AbstractObjectPtr& object) -> Result<PropertyValue> {
        return object->getProperty(DirectionProperty::key);
    };

    return getObject().and_then(onGetDirection).and_then(DirectionProperty::cast);
}

Result<void> AdapterRotable::setDirection(const DirectionProperty::type& value)
{
    const auto onSetDirection = [&value](const AbstractObjectPtr& object) -> Result<void> {
        return object->setProperty(DirectionProperty::key, value);
    };

    return getObject().and_then(onSetDirection);
}

Result<VelocityRotateProperty::type> AdapterRotable::getVelocityRotate() const
{
    const auto onGetVelocityRotate = [](const AbstractObjectPtr& object) -> Result<PropertyValue> {
        return object->getProperty(VelocityRotateProperty::key);
    };

    return getObject().and_then(onGetVelocityRotate).and_then(VelocityRotateProperty::cast);
}

}  // namespace otg