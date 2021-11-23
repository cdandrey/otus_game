#include "AdapterRotable.h"

#include <variant>

namespace otg {

AdapterRotable::AdapterRotable(const AbstractObjectPtr &obj)
    : m_obj {obj}
{
}

DirectionProperty::type_expected AdapterRotable::getDirection() const
{
	return m_obj->getProperty(DirectionProperty::key).and_then(DirectionProperty::cast);
}

PropertyResultSet AdapterRotable::setDirection(const PositionProperty::type &value)
{
	return m_obj->setProperty(DirectionProperty::key, value);
}

VelocityRotateProperty::type_expected AdapterRotable::getVelocityRotate() const
{
	return m_obj->getProperty(VelocityRotateProperty::key).and_then(VelocityProperty::cast);
}

}  // namespace otg