#pragma once

#include "AbstractAdapter.h"
#include "AbstractAdapterPropertys.h"

namespace otg {

class AbstractAdapterMovable
    : public AbstractAdapterPositionPropertyGetter
    , public AbstractAdapterVelocityPropertyGetter
    , public AbstractAdapterPositionPropertySetter
{
public:
    explicit AbstractAdapterMovable() = default;
    virtual ~AbstractAdapterMovable() = default;

    virtual Result<PositionProperty::type> getPosition() const = 0;
    virtual Result<void> setPosition(const PositionProperty::type& value) = 0;
    virtual Result<VelocityProperty::type> getVelocity() const = 0;
};

using AbstractAdapterMovablePtr = std::shared_ptr<AbstractAdapterMovable>;

class AdapterMovable : public AbstractAdapterMovable
{
public:
    explicit AdapterMovable(const AbstractObjectPtr& object);

    Result<PositionProperty::type> getPosition() const override;
    Result<void> setPosition(const PositionProperty::type& value) override;
    Result<VelocityProperty::type> getVelocity() const override;
};

}  // namespace otg