
#pragma once

#include "AbstractCommand.h"

namespace otg {

class CommandStop : public AbstractCommand
{
public:
	Result<void> execute() override;
};

}  // namespace otg