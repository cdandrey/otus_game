#pragma once

#include "AbstractCommand.h"
#include "AdapterRotable.h"

namespace otg {

class CommandRotable : public AbstractCommand
{
public:
	explicit CommandRotable(const AbstractRotablePtr &rotable);

	CommandResult execute() override;

private:
	AbstractRotablePtr m_rotable;
};

}  // namespace otg
