#pragma once

#include <memory>
#include <string>

#include "../types/ExceptionError.h"
#include "../types/Property.h"

namespace otg {

class AbstractObject
{
public:
	template<typename... Args>
	explicit AbstractObject(Args &&... args);

	virtual ~AbstractObject() = 0;

	ResultGet<PropertyValue> getProperty(PropertyKey key) const;
	ResultSet setProperty(PropertyKey key, const PropertyValue &value);

	virtual std::string typeName() const = 0;

private:
	PropertyMap m_propertys;

	ResultSet hasProperty(PropertyKey key) const;
};

using AbstractObjectPtr = std::shared_ptr<AbstractObject>;

template<typename... Args>
AbstractObject::AbstractObject(Args &&... args)
    : m_propertys {std::forward<Args>(args)...}
{
}

class ObjectTank : public AbstractObject
{
public:
	ObjectTank();

	std::string typeName() const override;
};

class ObjectBunker : public AbstractObject
{
public:
	ObjectBunker();

	std::string typeName() const override;
};

class ObjectTree : public AbstractObject
{
public:
	ObjectTree();

	std::string typeName() const override;
};
}  // namespace otg