#pragma once

#include "AbstractAdapter.h"

namespace otg {

#define SPECIFY_ABSTRACT_ADAPTER_PROPERTY_GETTER(Key) \
class AbstractAdapter##Key##PropertyGetter : virtual public AbstractAdapter \
{ \
public: \
    explicit AbstractAdapter##Key##PropertyGetter(const AbstractObjectPtr& object) \
        : AbstractAdapter{ object } {} \
\
    virtual ~AbstractAdapter##Key##PropertyGetter() = 0 {} \
    \
protected: \
\
    Result<Key##Property::type> get##Key##() const \
    { \
        const auto onGet = [](const AbstractObjectPtr& object) { \
            return object->getProperty(Key##Property::key).and_then(Key##Property::cast); \
        }; \
        return getObject().and_then(onGet); \
    } \
};

#define SPECIFY_ABSTRACT_ADAPTER_PROPERTY_SETTER(Key) \
class AbstractAdapter##Key##PropertySetter : virtual public AbstractAdapter \
{ \
public: \
    explicit AbstractAdapter##Key##PropertySetter(const AbstractObjectPtr& object) \
        : AbstractAdapter{ object } {} \
\
    virtual ~AbstractAdapter##Key##PropertySetter() = 0 {}\
\
protected: \
\
    Result<void> set##Key(const Key##Property::type& value) \
    { \
        const auto onSet = [&value](const AbstractObjectPtr& object) { \
            return object->setProperty(Key##Property::key, value); \
        };\
        return getObject().and_then(onSet); \
    } \
};

SPECIFY_ABSTRACT_ADAPTER_PROPERTY_GETTER(Position)
SPECIFY_ABSTRACT_ADAPTER_PROPERTY_GETTER(Velocity)
SPECIFY_ABSTRACT_ADAPTER_PROPERTY_GETTER(Direction)
SPECIFY_ABSTRACT_ADAPTER_PROPERTY_GETTER(VelocityRotate)
SPECIFY_ABSTRACT_ADAPTER_PROPERTY_GETTER(Fuel)

SPECIFY_ABSTRACT_ADAPTER_PROPERTY_SETTER(Position)
SPECIFY_ABSTRACT_ADAPTER_PROPERTY_SETTER(Direction)
SPECIFY_ABSTRACT_ADAPTER_PROPERTY_SETTER(Fuel)

}