#pragma once

#include "AbstractAdapter.h"
#include "AbstractAdapterPropertys.h"

namespace otg {

class AbstractAdapterRotable
    : public AbstractAdapterDirectionPropertyGetter
    , public AbstractAdapterVelocityRotatePropertyGetter
    , public AbstractAdapterDirectionPropertySetter
{
public:
    explicit AbstractAdapterRotable() = default;
    virtual ~AbstractAdapterRotable() = default;

    virtual Result<DirectionProperty::type> getDirection() const = 0;
    virtual Result<void> setDirection(const DirectionProperty::type& value) = 0;
    virtual Result<VelocityRotateProperty::type> getVelocityRotate() const = 0;
};

using AbstractAdapterRotablePtr = std::shared_ptr<AbstractAdapterRotable>;

class AdapterRotable : public AbstractAdapterRotable
{
public:
    explicit AdapterRotable(const AbstractObjectPtr& object);

    Result<DirectionProperty::type> getDirection() const override;
    Result<void> setDirection(const DirectionProperty::type& value) override;
    Result<VelocityRotateProperty::type> getVelocityRotate() const override;
};

}  // namespace otg