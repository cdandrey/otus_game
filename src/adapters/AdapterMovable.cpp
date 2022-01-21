#include "AdapterMovable.h"

#include <variant>

namespace otg {

AbstractAdapterMovable::AbstractAdapterMovable(const AbstractObjectPtr &object)
    : AbstractAdapter {object}
{
}

AdapterMovable::AdapterMovable(const AbstractObjectPtr &object)
    : AbstractAdapterMovable {object}
{
}

Result<PositionProperty::type> AdapterMovable::getPosition() const
{
	const auto onGetPosition = [](const AbstractObjectPtr &object) -> Result<PropertyValue> {
		return object->getProperty(PositionProperty::key);
	};

	return getObject().and_then(onGetPosition).and_then(PositionProperty::cast);
}

Result<void> AdapterMovable::setPosition(const PositionProperty::type &value)
{
	const auto onSetPosition = [&value](const AbstractObjectPtr &object) -> Result<void> {
		return object->setProperty(PositionProperty::key, value);
	};

	return getObject().and_then(onSetPosition);
}

Result<VelocityProperty::type> AdapterMovable::getVelocity() const
{
	const auto onGetVelocity = [](const AbstractObjectPtr &object) -> Result<PropertyValue> {
		return object->getProperty(VelocityProperty::key);
	};

	return getObject().and_then(onGetVelocity).and_then(VelocityProperty::cast);
}

}  // namespace otg