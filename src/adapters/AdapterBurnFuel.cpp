#include "AdapterBurnFuel.h"

#include <variant>

namespace otg {

AbstractAdapterMovableBurnFuel::AbstractAdapterMovableBurnFuel(const AbstractObjectPtr& object)
    : AbstractAdapterFuelPropertyGetter{ object }
    , AbstractAdapterVelocityPropertyGetter{ object }
    , AbstractAdapterFuelPropertySetter{ object }
{
}

AdapterMovableBurnFuel::AdapterMovableBurnFuel(const AbstractObjectPtr& object)
    : AbstractAdapter{ object }
    , AbstractAdapterMovableBurnFuel{ object }
{
}

Result<FuelProperty::type> AdapterMovableBurnFuel::getFuel() const
{
    return AbstractAdapterFuelPropertyGetter::getFuel();
}

Result<VelocityProperty::type> AdapterMovableBurnFuel::getVelocity() const
{
    return AbstractAdapterVelocityPropertyGetter::getVelocity();
}

AbstractAdapterRotableBurnFuel::AbstractAdapterRotableBurnFuel(const AbstractObjectPtr& object)
    : AbstractAdapterFuelPropertyGetter{ object }
    , AbstractAdapterVelocityRotatePropertyGetter{ object }
    , AbstractAdapterFuelPropertySetter{ object }
{
}

AdapterRotableBurnFuel::AdapterRotableBurnFuel(const AbstractObjectPtr& object)
    : AbstractAdapter{ object }
    , AbstractAdapterRotableBurnFuel{ object }
{
}

Result<FuelProperty::type> AdapterRotableBurnFuel::getFuel() const
{
    return AbstractAdapterFuelPropertyGetter::getFuel();
}

Result<VelocityRotateProperty::type> AdapterRotableBurnFuel::getVelocityRotate() const
{
    return AbstractAdapterVelocityRotatePropertyGetter::getVelocityRotate();
}

}  // namespace otg