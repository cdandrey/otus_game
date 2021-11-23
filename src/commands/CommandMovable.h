#pragma once

#include "AbstractCommand.h"
#include "AdapterMovable.h"

namespace otg {

class CommandMovable : public AbstractCommand
{
public:
	explicit CommandMovable(const AbstractMovablePtr &movable);

	CommandResult execute() override;

private:
	AbstractMovablePtr m_movable;
};

}  // namespace otg