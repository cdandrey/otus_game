#include "AdapterRotable.h"

#include <variant>

namespace otg {

AdapterRotable::AdapterRotable(const AbstractObjectPtr &obj)
    : m_obj{obj}
{}


DirectionProperty::type AdapterRotable::getDirection() const
{
    using Type = DirectionProperty::type;

    return m_obj->extractPropertyValue<Type>(m_obj->getProperty(DirectionProperty::key));
}

void AdapterRotable::setDirection(const PositionProperty::type& value)
{
    m_obj->setProperty(DirectionProperty::key,value);
}

VelocityRotateProperty::type AdapterRotable::getVelocityRotate() const
{
    using Type = VelocityRotateProperty::type;

    return m_obj->extractPropertyValue<Type>(m_obj->getProperty(VelocityRotateProperty::key));
}

AbstractObjectPtr AdapterRotable::getObject() const
{
    return m_obj;
}

}