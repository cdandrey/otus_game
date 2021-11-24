#pragma once

#include "AbstractCommand.h"
#include "AdapterMovable.h"

namespace otg {

class CommandMovable : public AbstractCommand
{
public:
	explicit CommandMovable(const AbstractMovablePtr &movable);

	PropertyResultSet execute() override;

	void setAdapter(const AbstractMovablePtr &movable);

protected:
	AdapterMovableResultGet getAdapter() const;

private:
	AbstractMovablePtr m_movable;
};

}  // namespace otg