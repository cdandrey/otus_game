#pragma once

#include "AbstractCommand.h"
#include "AdapterMovable.h"

namespace otg {

class CommandMovable : public AbstractCommand
{
public:
	explicit CommandMovable(const AbstractAdapterMovablePtr &movable);

	ResultSet execute() override;

private:
	AbstractAdapterMovablePtr m_movable;
};

}  // namespace otg