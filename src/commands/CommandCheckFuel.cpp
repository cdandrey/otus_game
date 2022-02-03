
#include "CommandCheckFuel.h"

#include <cmath>

namespace otg {

CommandMovableCheckFuel::CommandMovableCheckFuel(const AbstractAdapterMovableCheckFuelPtr& checkFuel)
    : m_checkFuel{ checkFuel }
{
}

Result<void> CommandMovableCheckFuel::execute()
{
    const auto onGetVelocity = [this](const VelocityProperty::type& velocity) -> Result<void> {
        const auto onGetFuel = [this, &velocity](const FuelProperty::type& fuel) -> Result<void> {
            const auto movementLenght = (velocity.dp.x * velocity.dp.x) + (velocity.dp.y * velocity.dp.y);
            if (movementLenght > (fuel * fuel))
            {
                return makeUnexpected(ExceptionErrorType::CommandExeption);
            }
            return {};
        };

        return m_checkFuel->getFuel().and_then(onGetFuel);
    };
    return m_checkFuel->getVelocity().and_then(onGetVelocity);
}

CommandRotableCheckFuel::CommandRotableCheckFuel(const AbstractAdapterRotableCheckFuelPtr& checkFuel)
    : m_checkFuel{ checkFuel }
{
}

Result<void> CommandRotableCheckFuel::execute()
{
    const auto onGetVelocityRotate = [this](const VelocityRotateProperty::type& velocity) -> Result<void> {
        const auto onGetFuel = [this, &velocity](const FuelProperty::type& fuel) -> Result<void> {
            const auto rotateLenght = (velocity.da.a * velocity.da.a) + (velocity.da.a * velocity.da.a);
            if (rotateLenght * fuelConsumption > (fuel * fuel))
            {
                return makeUnexpected(ExceptionErrorType::CommandExeption);
            }
            return {};
        };

        return m_checkFuel->getFuel().and_then(onGetFuel);
    };
    return m_checkFuel->getVelocityRotate().and_then(onGetVelocityRotate);
}

}  // namespace otg