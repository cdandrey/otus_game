#pragma once

#include "AbstractCommand.h"
#include "AdapterRotable.h"

namespace otg {

class CommandRotable : public AbstractCommand
{
public:
	explicit CommandRotable(const AbstractRotablePtr &rotable);

	ResultSet execute() override;

	void setAdapetr(const AbstractRotablePtr &rotable);

protected:
	ResultGet<AbstractRotablePtr> getAdapter() const;

private:
	AbstractRotablePtr m_rotable;
};

}  // namespace otg
