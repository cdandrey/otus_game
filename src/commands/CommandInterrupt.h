
#pragma once

#include "AbstractCommand.h"

namespace otg {

class CommandInterrupt : public AbstractCommand
{
public:
	Result<void> execute() override;
};

}  // namespace otg