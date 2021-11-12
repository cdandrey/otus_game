#include "AdapterMovable.h"

#include <variant>

namespace otg {

AdapterMovable::AdapterMovable(const AbstractObjectPtr &obj)
    : m_obj{obj}
{}


PositionProperty::type AdapterMovable::getPosition() const
{
    using Type = PositionProperty::type;

    return m_obj->extractPropertyValue<Type>(m_obj->getProperty(PositionProperty::key));
}

void AdapterMovable::setPosition(const PositionProperty::type& value)
{
    m_obj->setProperty(PositionProperty::key,value);
}

VelocityProperty::type AdapterMovable::getVelocity() const
{
    using Type = VelocityProperty::type;

    return m_obj->extractPropertyValue<Type>(m_obj->getProperty(VelocityProperty::key));
}

}