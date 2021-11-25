#include "AdapterRotable.h"

#include <variant>

namespace otg {

AbstractRotable::AbstractRotable(const AbstractObjectPtr &object)
    : m_object {object}
{
}

void AbstractRotable::setObject(const AbstractObjectPtr &object)
{
	if (m_object != object) {
		m_object = object;
	}
}

ResultGet<AbstractObjectPtr> AbstractRotable::getObject() const
{
	if (m_object != nullptr) {
		return m_object;
	}

	return makeUnexpected(ExceptionErrorType::NotInitialized, std::string {"Object of rotable adapter is not initialized"});
};

AdapterRotable::AdapterRotable(const AbstractObjectPtr &object)
    : AbstractRotable {object}
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