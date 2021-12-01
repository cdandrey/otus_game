#include "Objects.h"

#include <typeinfo>

namespace otg {

AbstractObject::~AbstractObject()
{
}

Result<PropertyValue> AbstractObject::getProperty(PropertyKey key) const
{
	return hasProperty(key).map([this, key]() -> PropertyValue {
		return m_propertys.at(key);
	});
}

Result<void> AbstractObject::setProperty(PropertyKey key, const PropertyValue &value)
{
	const auto onSuccess = [this, key, value]() {
		m_propertys[key] = value;
	};

	return hasProperty(key).map(onSuccess);
}

Result<void> AbstractObject::hasProperty(PropertyKey key) const
{
	if (m_propertys.find(key) != m_propertys.end()) {
		return {};
	}

	std::string msg {"Object " + std::string {typeid(*this).name()} + " does not have the property " + std::string {key}};
	return makeUnexpected(ExceptionErrorType::Missing, msg);
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

ObjectBunker::ObjectBunker()
    : AbstractObject {std::pair {PositionProperty::key, PositionProperty::type {}},
                      std::pair {HealthProperty::key, HealthProperty::type {}},
                      std::pair {FuelProperty::key, FuelProperty::type {}},
                      std::pair {AmmoProperty::key, AmmoProperty::type {}},
                      std::pair {DirectionProperty::key, AmmoProperty::type {}}}
{
}

ObjectTree::ObjectTree()
    : AbstractObject {std::pair {PositionProperty::key, PositionProperty::type {}}, std::pair {HealthProperty::key, HealthProperty::type {}}}
{
}

}  // namespace otg