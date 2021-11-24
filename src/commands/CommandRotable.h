#pragma once

#include "AbstractCommand.h"
#include "AdapterRotable.h"

namespace otg {

class CommandRotable : public AbstractCommand
{
public:
	explicit CommandRotable(const AbstractRotablePtr &rotable);

	PropertyResultSet execute() override;

	void set(const AbstractRotablePtr &rotable);

private:
	AbstractRotablePtr m_rotable;
};

}  // namespace otg
