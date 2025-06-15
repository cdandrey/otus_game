
#pragma once

#include "AbstractCommand.h"
#include "adapters/AdapterCheckFuel.h"

namespace otg {

class CommandMovableCheckFuel : public AbstractCommand
{
public:
    explicit CommandMovableCheckFuel(const AbstractAdapterMovableCheckFuelPtr& checkFuel);

    Result<void> execute() override;

private:
    AbstractAdapterMovableCheckFuelPtr m_checkFuel;
};

class CommandRotableCheckFuel : public AbstractCommand
{
public:
    explicit CommandRotableCheckFuel(const AbstractAdapterRotableCheckFuelPtr& checkFuel);

    Result<void> execute() override;

private:
    AbstractAdapterRotableCheckFuelPtr m_checkFuel;
    const float fuelConsumption{ 0.01f };
};

}  // namespace otg