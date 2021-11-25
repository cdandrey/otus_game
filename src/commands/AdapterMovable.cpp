#include "AdapterMovable.h"

#include <variant>

namespace otg {

AbstractMovable::AbstractMovable(const AbstractObjectPtr &object)
    : m_object {object}
{
}

void AbstractMovable::setObject(const AbstractObjectPtr &object)
{
	if (m_object != object) {
		m_object = object;
	}
}

ResultGet<AbstractObjectPtr> AbstractMovable::getObject() const
{
	if (m_object != nullptr) {
		return m_object;
	}

	return makeUnexpected(ExceptionErrorType::NotInitialized, std::string {"Object of movable adapter is not initialized"});
}

AdapterMovable::AdapterMovable(const AbstractObjectPtr &object)
    : AbstractMovable {object}
{
}

ResultGet<PositionProperty::type> AdapterMovable::getPosition() const
{
	const auto onGetPosition = [](const AbstractObjectPtr &object) -> ResultGet<PropertyValue> {
		return object->getProperty(PositionProperty::key);
	};

	return getObject().and_then(onGetPosition).and_then(PositionProperty::cast);
}

ResultSet AdapterMovable::setPosition(const PositionProperty::type &value)
{
	const auto onSetPosition = [&value](const AbstractObjectPtr &object) -> ResultSet {
		return object->setProperty(PositionProperty::key, value);
	};

	return getObject().and_then(onSetPosition);
}

ResultGet<VelocityProperty::type> AdapterMovable::getVelocity() const
{
	const auto onGetVelocity = [](const AbstractObjectPtr &object) -> ResultGet<PropertyValue> {
		return object->getProperty(VelocityProperty::key);
	};

	return getObject().and_then(onGetVelocity).and_then(VelocityProperty::cast);
}

}  // namespace otg