#pragma once

#include <memory>
#include <string>

#include "../types/Property.h"

namespace otg
{

class AbstractObject
{
public:

    template <typename... Args>
    explicit AbstractObject(Args &&...args);

    virtual ~AbstractObject() = 0;

    PropertyValueOpt getProperty(PropertyKey key) const;
    void setProperty(PropertyKey key, const PropertyValue &value);

    template<typename T>
    T extractPropertyValue(const PropertyValueOpt &value) const;

private:
    PropertyMap m_propertys;

    bool hasProperty(PropertyKey key) const;
};

using AbstractObjectPtr = std::shared_ptr<AbstractObject>;

template <typename... Args>
AbstractObject::AbstractObject(Args &&...args)
    : m_propertys{std::forward<Args>(args)...} {}

template<typename T>
T AbstractObject::extractPropertyValue(const PropertyValueOpt &value) const
{
    try {
        return std::any_cast<T>(value.value_or(T{}));
    }
    catch(std::bad_any_cast&) {
    }

    return T{};
}

class ObjectTank : public AbstractObject
{
public:
    ObjectTank();
};

class ObjectBunker : public AbstractObject
{
public:
    ObjectBunker();
};

class ObjectTree : public AbstractObject
{
public:
    ObjectTree();
};
}