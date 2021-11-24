#pragma once

#include "AbstractCommand.h"
#include "AdapterRotable.h"

namespace otg {

class CommandRotable : public AbstractCommand
{
public:
	explicit CommandRotable(const AbstractRotablePtr &rotable);

	PropertyResultSet execute() override;

	void setAdapetr(const AbstractRotablePtr &rotable);

protected:
	AdapapterRotableResultGet getAdapter() const;

private:
	AbstractRotablePtr m_rotable;
};

}  // namespace otg
