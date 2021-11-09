#include "AdapterMovable.h"

#include <variant>

namespace otg {

AdapterMovable::AdapterMovable(const AbstractObjectPtr &obj)
    : m_obj{obj}
{}


PositionProperty::type AdapterMovable::getPosition() const
{
    using Type = PositionProperty::type;

    try {
        return std::any_cast<Type>(m_obj->getProperty(PositionProperty::key).value_or(Type{}));
    } 
    catch (std::bad_variant_access&) {
    }

    return Type{};
}

void AdapterMovable::setPosition(const PositionProperty::type& value)
{
    m_obj->setProperty(PositionProperty::key,value);
}

VelocityProperty::type AdapterMovable::getVelocity() const
{
    using Type = VelocityProperty::type;

    try {
        return std::any_cast<Type>(m_obj->getProperty(VelocityProperty::key).value_or(Type{}));
    } 
    catch (std::bad_variant_access&) {
    }

    return Type{};
}

AbstractObjectPtr AdapterMovable::getObject() const
{
    return m_obj;
}

}