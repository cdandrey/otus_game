#include "AdapterCheckFuel.h"

#include <variant>

namespace otg {

AbstractAdapterMovableCheckFuel::AbstractAdapterMovableCheckFuel(const AbstractObjectPtr& object)
    : AbstractAdapterFuelPropertyGetter{ object }
    , AbstractAdapterVelocityPropertyGetter{ object }
{
}

AdapterMovableCheckFuel::AdapterMovableCheckFuel(const AbstractObjectPtr& object)
    : AbstractAdapter{ object }
    , AbstractAdapterMovableCheckFuel{ object }
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

AbstractAdapterRotableCheckFuel::AbstractAdapterRotableCheckFuel(const AbstractObjectPtr& object)
    : AbstractAdapterFuelPropertyGetter{ object }
    , AbstractAdapterVelocityRotatePropertyGetter{ object }
{
}

AdapterRotableCheckFuel::AdapterRotableCheckFuel(const AbstractObjectPtr& object)
    : AbstractAdapter{ object }
    , AbstractAdapterRotableCheckFuel{ object }
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