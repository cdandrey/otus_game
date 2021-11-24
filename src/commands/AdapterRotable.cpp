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

AbstractObjectPtr AbstractRotable::getObject() const
{
	return m_object;
};

AdapterRotable::AdapterRotable(const AbstractObjectPtr &object)
    : AbstractRotable {object}
{
}

DirectionProperty::type_expected AdapterRotable::getDirection() const
{
	return getObject()->getProperty(DirectionProperty::key).and_then(DirectionProperty::cast);
}

PropertyResultSet AdapterRotable::setDirection(const PositionProperty::type &value)
{
	return getObject()->setProperty(DirectionProperty::key, value);
}

VelocityRotateProperty::type_expected AdapterRotable::getVelocityRotate() const
{
	return getObject()->getProperty(VelocityRotateProperty::key).and_then(VelocityProperty::cast);
}

}  // namespace otg