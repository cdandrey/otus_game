#pragma once

#include "../types/Property.h"
#include <memory>

namespace otg {

class AbstractCommand
{
public:
	virtual ~AbstractCommand() = default;

	virtual Result<void> execute() = 0;
};

using AbstractCommandPtr = std::shared_ptr<AbstractCommand>;

}  // namespace otg