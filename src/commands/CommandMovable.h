#pragma once

#include "AbstractCommand.h"
#include "AdapterMovable.h"

namespace otg {

class CommandMovable : public AbstractCommand
{
public:
	explicit CommandMovable(const AbstractMovablePtr &movable);

	ResultSet execute() override;

	void setAdapter(const AbstractMovablePtr &movable);

protected:
	ResultGet<AbstractMovablePtr> getAdapter() const;

private:
	AbstractMovablePtr m_movable;
};

}  // namespace otg