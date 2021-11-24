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

AbstractObjectPtr AbstractMovable::getObject() const
{
	return m_object;
}

AdapterMovable::AdapterMovable(const AbstractObjectPtr &object)
    : AbstractMovable {object}
{
}

PositionProperty::type_expected AdapterMovable::getPosition() const
{
	return getObject()->getProperty(PositionProperty::key).and_then(PositionProperty::cast);
}

PropertyResultSet AdapterMovable::setPosition(const PositionProperty::type &value)
{
	return getObject()->setProperty(PositionProperty::key, value);
}

VelocityProperty::type_expected AdapterMovable::getVelocity() const
{
	return getObject()->getProperty(VelocityProperty::key).and_then(VelocityProperty::cast);
}

}  // namespace otg