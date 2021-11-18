#include "AdapterMovable.h"

#include <variant>

namespace otg {

AdapterMovable::AdapterMovable(const AbstractObjectPtr &obj)
    : m_obj{obj}
{}


PositionProperty::type AdapterMovable::getPosition() const
{
    return PositionProperty::cast(m_obj->getProperty(PositionProperty::key).value());
}

void AdapterMovable::setPosition(const PositionProperty::type& value)
{
    m_obj->setProperty(PositionProperty::key,value);
}

VelocityProperty::type AdapterMovable::getVelocity() const
{
    return VelocityProperty::cast(m_obj->getProperty(VelocityProperty::key).value());
}

}