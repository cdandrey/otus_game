#pragma once

#include "AbstractCommand.h"
#include "AdapterMovable.h"

namespace otg {

class CommandMovable : public AbstractCommand
{
public:
	explicit CommandMovable(const AbstractMovablePtr &movable);

	PropertyResultSet execute() override;

	void set(const AbstractMovablePtr &movable);

private:
	AbstractMovablePtr m_movable;
};

}  // namespace otg