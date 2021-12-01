#pragma once

#include "AbstractCommand.h"
#include "AdapterRotable.h"

namespace otg {

class CommandRotable : public AbstractCommand
{
public:
	explicit CommandRotable(const AbstractAdapterRotablePtr &rotable);

	Result<void> execute() override;

private:
	AbstractAdapterRotablePtr m_rotable;
};

}  // namespace otg
