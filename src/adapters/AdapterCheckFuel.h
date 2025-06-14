#pragma once

#include "AbstractAdapter.h"
#include "AbstractAdapterPropertys.h"

namespace otg {

class AbstractAdapterMovableCheckFuel
    : public AbstractAdapterFuelPropertyGetter
    , public AbstractAdapterVelocityPropertyGetter
{
public:
    explicit AbstractAdapterMovableCheckFuel() = default;
    virtual ~AbstractAdapterMovableCheckFuel() = default;

    virtual Result<FuelProperty::type> getFuel() const = 0;
    virtual Result<VelocityProperty::type> getVelocity() const = 0;
};

using AbstractAdapterMovableCheckFuelPtr = std::shared_ptr<AbstractAdapterMovableCheckFuel>;

class AdapterMovableCheckFuel : public AbstractAdapterMovableCheckFuel
{
public:
    explicit AdapterMovableCheckFuel(const AbstractObjectPtr& object);

    Result<FuelProperty::type> getFuel() const override;
    Result<VelocityProperty::type> getVelocity() const override;
};

class AbstractAdapterRotableCheckFuel
    : public AbstractAdapterFuelPropertyGetter
    , public AbstractAdapterVelocityRotatePropertyGetter
{
public:
    explicit AbstractAdapterRotableCheckFuel() = default;
    virtual ~AbstractAdapterRotableCheckFuel() = default;

    virtual Result<FuelProperty::type> getFuel() const = 0;
    virtual Result<VelocityRotateProperty::type> getVelocityRotate() const = 0;
};

using AbstractAdapterRotableCheckFuelPtr = std::shared_ptr<AbstractAdapterRotableCheckFuel>;

class AdapterRotableCheckFuel : public AbstractAdapterRotableCheckFuel
{
public:
    explicit AdapterRotableCheckFuel(const AbstractObjectPtr& object);

    Result<FuelProperty::type> getFuel() const override;
    Result<VelocityRotateProperty::type> getVelocityRotate() const override;
};

}