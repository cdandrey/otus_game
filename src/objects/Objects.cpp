#include "Objects.h"

namespace otg {

AbstractObject::~AbstractObject()
{
}

PropertyResultGet AbstractObject::getProperty(PropertyKey key) const
{
	if (hasProperty(key)) {
		return m_propertys.at(key);
	}

	std::string errorMsg {"Object " + typeName() + " does not have the property " + std::string {key}};
	return makePropertyUnexpected(PropertyErrorType::Missing, errorMsg);
}

PropertyResultSet AbstractObject::setProperty(PropertyKey key, const PropertyValue &value)
{
	if (hasProperty(key)) {
		m_propertys[key] = value;
		return {};
	}

	std::string errorMsg {"Object " + typeName() + " does not have the property " + std::string {key}};
	return makePropertyUnexpected(PropertyErrorType::Missing, errorMsg);
}

bool AbstractObject::hasProperty(PropertyKey key) const
{
	return m_propertys.find(key) != m_propertys.end();
}

ObjectTank::ObjectTank()
    : AbstractObject {std::pair {PositionProperty::key, PositionProperty::type {}},
                      std::pair {VelocityProperty::key, VelocityProperty::type {}},
                      std::pair {HealthProperty::key, HealthProperty::type {}},
                      std::pair {FuelProperty::key, FuelProperty::type {}},
                      std::pair {AmmoProperty::key, AmmoProperty::type {}},
                      std::pair {DirectionProperty::key, AmmoProperty::type {}},
                      std::pair {VelocityRotateProperty::key, VelocityProperty::type {}}}
{
}

std::string ObjectTank::typeName() const
{
	return "Tank";
}

ObjectBunker::ObjectBunker()
    : AbstractObject {std::pair {PositionProperty::key, PositionProperty::type {}},
                      std::pair {HealthProperty::key, HealthProperty::type {}},
                      std::pair {FuelProperty::key, FuelProperty::type {}},
                      std::pair {AmmoProperty::key, AmmoProperty::type {}},
                      std::pair {DirectionProperty::key, AmmoProperty::type {}}}
{
}

std::string ObjectBunker::typeName() const
{
	return "Bunker";
}

ObjectTree::ObjectTree()
    : AbstractObject {std::pair {PositionProperty::key, PositionProperty::type {}}, std::pair {HealthProperty::key, HealthProperty::type {}}}
{
}

std::string ObjectTree::typeName() const
{
	return "Tree";
}

}  // namespace otg