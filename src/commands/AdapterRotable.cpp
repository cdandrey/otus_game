#include "AdapterRotable.h"

#include <variant>

namespace otg {

AbstractAdapterRotable::AbstractAdapterRotable(const AbstractObjectPtr &object)
    : AbstractAdapter {object}
{
}

AdapterRotable::AdapterRotable(const AbstractObjectPtr &object)
    : AbstractAdapterRotable {object}
{
}

ResultGet<DirectionProperty::type> AdapterRotable::getDirection() const
{
	const auto onGetDirection = [](const AbstractObjectPtr &object) -> ResultGet<PropertyValue> {
		return object->getProperty(DirectionProperty::key);
	};

	return getObject().and_then(onGetDirection).and_then(DirectionProperty::cast);
}

ResultSet AdapterRotable::setDirection(const PositionProperty::type &value)
{
	const auto onSetDirection = [&value](const AbstractObjectPtr &object) -> ResultSet {
		return object->setProperty(DirectionProperty::key, value);
	};

	return getObject().and_then(onSetDirection);
}

ResultGet<VelocityRotateProperty::type> AdapterRotable::getVelocityRotate() const
{
	const auto onGetVelocityRotate = [](const AbstractObjectPtr &object) -> ResultGet<PropertyValue> {
		return object->getProperty(VelocityRotateProperty::key);
	};

	return getObject().and_then(onGetVelocityRotate).and_then(DirectionProperty::cast);
}

}  // namespace otg