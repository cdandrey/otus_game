#include "AdapterBurnFuel.h"

#include <variant>

namespace otg {

AdapterMovableBurnFuel::AdapterMovableBurnFuel(const AbstractObjectPtr& object)
    : AbstractAdapter{ object }
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

AdapterRotableBurnFuel::AdapterRotableBurnFuel(const AbstractObjectPtr& object)
    : AbstractAdapter{ object }
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