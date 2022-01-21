#pragma once

#include "AbstractCommand.h"
#include "../adapters/AdapterMovable.h"

namespace otg {

class CommandMovable : public AbstractCommand
{
public:
    explicit CommandMovable(const AbstractAdapterMovablePtr& movable);

    Result<void> execute() override;

private:
    AbstractAdapterMovablePtr m_movable;
};

}  // namespace otg