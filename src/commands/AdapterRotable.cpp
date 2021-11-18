#include "AdapterRotable.h"

#include <variant>

namespace otg {

AdapterRotable::AdapterRotable(const AbstractObjectPtr &obj)
    : m_obj{obj}
{}


DirectionProperty::type AdapterRotable::getDirection() const
{
    return DirectionProperty::cast(m_obj->getProperty(DirectionProperty::key).value());
}

void AdapterRotable::setDirection(const PositionProperty::type& value)
{
    m_obj->setProperty(DirectionProperty::key,value);
}

VelocityRotateProperty::type AdapterRotable::getVelocityRotate() const
{
    return VelocityProperty::cast(m_obj->getProperty(VelocityRotateProperty::key).value());
}

}