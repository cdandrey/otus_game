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
        std::pair{PositionProperty::key,PositionProperty::type{}},
        std::pair{VelocityProperty::key,VelocityProperty::type{}},
        std::pair{HealthProperty::key,HealthProperty::type{}},
        std::pair{FuelProperty::key,FuelProperty::type{}},
        std::pair{AmmoProperty::key,AmmoProperty::type{}},
        std::pair{DirectionProperty::key,AmmoProperty::type{}},
        std::pair{VelocityRotateProperty::key,VelocityProperty::type{}}
    }
{
}

ObjectBunker::ObjectBunker()
    : AbstractObject{
        std::pair{PositionProperty::key,PositionProperty::type{}},
        std::pair{HealthProperty::key,HealthProperty::type{}},
        std::pair{FuelProperty::key,FuelProperty::type{}},
        std::pair{AmmoProperty::key,AmmoProperty::type{}},
        std::pair{DirectionProperty::key,AmmoProperty::type{}}
    }
{
}

ObjectTree::ObjectTree()
    : AbstractObject{
        std::pair{PositionProperty::key,PositionProperty::type{}},
        std::pair{HealthProperty::key,HealthProperty::type{}}
    }
{
}

}