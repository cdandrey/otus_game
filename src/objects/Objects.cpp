#include "Objects.h"

namespace otg {

AbstractObject::~AbstractObject() {}

PropertyValueOpt AbstractObject::getProperty(PropertyKey key) const
{
    if (hasProperty(key)) {
        return m_propertys.at(key);
    }

    return std::nullopt;
}

void AbstractObject::setProperty(PropertyKey key,const PropertyValue &value)
{
    if (hasProperty(key)) {
        m_propertys[key] = value;
    }
}

bool AbstractObject::hasProperty(PropertyKey key) const
{
    return m_propertys.find(key) != m_propertys.end();
}

ObjectTank::ObjectTank()
    : AbstractObject{
        PositionProperty::init_value,
        VelocityProperty::init_value,
        HealthProperty::init_value,
        FuelProperty::init_value,
        AmmoProperty::init_value,
        DirectionProperty::init_value,
        VelocityRotateProperty::init_value
    }
{
}

ObjectBunker::ObjectBunker()
    : AbstractObject{
        PositionProperty::init_value,
        HealthProperty::init_value,
        FuelProperty::init_value,
        AmmoProperty::init_value,
        DirectionProperty::init_value
    }
{
}

ObjectTree::ObjectTree()
    : AbstractObject{
        PositionProperty::init_value,
        HealthProperty::init_value
    }
{
}

}