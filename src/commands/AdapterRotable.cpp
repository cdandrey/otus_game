#include "AdapterRotable.h"

#include <variant>

namespace otg {

AdapterRotable::AdapterRotable(const AbstractObjectPtr &obj)
    : m_obj{obj}
{}


DirectionProperty::type AdapterRotable::getDirection() const
{
    using Type = DirectionProperty::type;

    try {
        return std::get<Type>(m_obj->getProperty(DirectionProperty::key).value_or(Type{}));
    } 
    catch (std::bad_variant_access&) {
    }

    return Type{};
}

void AdapterRotable::setDirection(const PositionProperty::type& value)
{
    m_obj->setProperty(DirectionProperty::key,value);
}

VelocityRotateProperty::type AdapterRotable::getVelocityRotate() const
{
    using Type = VelocityRotateProperty::type;

    try {
        return std::get<Type>(m_obj->getProperty(VelocityRotateProperty::key).value_or(Type{}));
    } 
    catch (std::bad_variant_access&) {
    }

    return Type{};
}

AbstractObjectPtr AdapterRotable::getObject() const
{
    return m_obj;
}

}