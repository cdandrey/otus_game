#include "AdapterCheckFuel.h"

#include <variant>

namespace otg {

AdapterMovableCheckFuel::AdapterMovableCheckFuel(const AbstractObjectPtr& object)
    : AbstractAdapter{ object }
{
}

Result<FuelProperty::type> AdapterMovableCheckFuel::getFuel() const
{
    return AbstractAdapterFuelPropertyGetter::getFuel();
}

Result<VelocityProperty::type> AdapterMovableCheckFuel::getVelocity() const
{
    return AbstractAdapterVelocityPropertyGetter::getVelocity();
}

AdapterRotableCheckFuel::AdapterRotableCheckFuel(const AbstractObjectPtr& object)
    : AbstractAdapter{ object }
{
}

Result<FuelProperty::type> AdapterRotableCheckFuel::getFuel() const
{
    return AbstractAdapterFuelPropertyGetter::getFuel();
}

Result<VelocityRotateProperty::type> AdapterRotableCheckFuel::getVelocityRotate() const
{
    return AbstractAdapterVelocityRotatePropertyGetter::getVelocityRotate();
}

}  // namespace otg