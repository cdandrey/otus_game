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

ObjectResultGet AbstractMovable::getObject() const
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

PositionProperty::type_expected AdapterMovable::getPosition() const
{
	const auto onGetPosition = [](const AbstractObjectPtr &object) -> PropertyResultGet {
		return object->getProperty(PositionProperty::key);
	};

	return getObject().and_then(onGetPosition).and_then(PositionProperty::cast);
}

PropertyResultSet AdapterMovable::setPosition(const PositionProperty::type &value)
{
	const auto onSetPosition = [&value](const AbstractObjectPtr &object) -> PropertyResultSet {
		return object->setProperty(PositionProperty::key, value);
	};

	return getObject().and_then(onSetPosition);
}

VelocityProperty::type_expected AdapterMovable::getVelocity() const
{
	const auto onGetVelocity = [](const AbstractObjectPtr &object) -> PropertyResultGet {
		return object->getProperty(VelocityProperty::key);
	};

	return getObject().and_then(onGetVelocity).and_then(VelocityProperty::cast);
}

}  // namespace otg