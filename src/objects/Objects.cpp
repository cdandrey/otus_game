#include "Objects.h"

namespace otg {

AbstractObject::~AbstractObject()
{
}

PropertyResultGet AbstractObject::getProperty(PropertyKey key) const
{
	return hasProperty(key).map([this, key](std::true_type) -> PropertyValue {
		return m_propertys.at(key);
	});
}

PropertyResultSet AbstractObject::setProperty(PropertyKey key, const PropertyValue &value)
{
	const auto onSuccess = [this, key, value](std::true_type) -> std::true_type {
		m_propertys[key] = value;
		return {};
	};
	return hasProperty(key).map(onSuccess);
}

PropertyResultSet AbstractObject::hasProperty(PropertyKey key) const
{
	if (m_propertys.find(key) != m_propertys.end()) {
		return std::true_type {};
	}

	std::string errorMsg {"Object " + typeName() + " does not have the property " + std::string {key}};
	return makeUnexpected(ExceptionErrorType::Missing, errorMsg);
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