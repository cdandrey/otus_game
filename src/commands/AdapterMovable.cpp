#include "AdapterMovable.h"

#include <variant>

namespace otg {

AdapterMovable::AdapterMovable(const AbstractObjectPtr &obj)
    : m_obj {obj}
{
}

PositionProperty::type_expected AdapterMovable::getPosition() const
{
	return m_obj->getProperty(PositionProperty::key).and_then(PositionProperty::cast);
}

PropertyResultSet AdapterMovable::setPosition(const PositionProperty::type &value)
{
	return m_obj->setProperty(PositionProperty::key, value);
}

VelocityProperty::type_expected AdapterMovable::getVelocity() const
{
	return m_obj->getProperty(VelocityProperty::key).and_then(VelocityProperty::cast);
}

}  // namespace otg