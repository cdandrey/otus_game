#pragma once

#include "AbstractAdapter.h"
#include "AbstractAdapterPropertys.h"

namespace otg {

class AbstractAdapterMovableBurnFuel
    : public AbstractAdapterFuelPropertyGetter
    , public AbstractAdapterFuelPropertySetter
    , public AbstractAdapterVelocityPropertyGetter
{
public:
    explicit AbstractAdapterMovableBurnFuel() = default;
    virtual ~AbstractAdapterMovableBurnFuel() = default;

    virtual Result<FuelProperty::type> getFuel() const = 0;
    virtual Result<void> setFuel(const FuelProperty::type& value) = 0;
    virtual Result<VelocityProperty::type> getVelocity() const = 0;
};

using AbstractAdapterMovableBurnFuelPtr = std::shared_ptr<AbstractAdapterMovableBurnFuel>;

class AdapterMovableBurnFuel : public AbstractAdapterMovableBurnFuel
{
public:
    explicit AdapterMovableBurnFuel(const AbstractObjectPtr& object);

    Result<FuelProperty::type> getFuel() const override;
    Result<void> setFuel(const FuelProperty::type& value) override;
    Result<VelocityProperty::type> getVelocity() const override;
};

class AbstractAdapterRotableBurnFuel
    : public AbstractAdapterFuelPropertyGetter
    , public AbstractAdapterFuelPropertySetter
    , public AbstractAdapterVelocityRotatePropertyGetter
{
public:
    explicit AbstractAdapterRotableBurnFuel() = default;
    virtual ~AbstractAdapterRotableBurnFuel() = default;

    virtual Result<FuelProperty::type> getFuel() const = 0;
    virtual Result<void> setFuel(const FuelProperty::type& value) = 0;
    virtual Result<VelocityRotateProperty::type> getVelocityRotate() const = 0;
};

using AbstractAdapterRotableBurnFuelPtr = std::shared_ptr<AbstractAdapterRotableBurnFuel>;

class AdapterRotableBurnFuel : public AbstractAdapterRotableBurnFuel
{
public:
    explicit AdapterRotableBurnFuel(const AbstractObjectPtr& object);

    Result<FuelProperty::type> getFuel() const override;
    Result<void> setFuel(const FuelProperty::type& value) override;
    Result<VelocityRotateProperty::type> getVelocityRotate() const override;
};

}