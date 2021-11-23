#pragma once

#include "../types/Property.h"
#include <memory>

namespace otg {

using CommandResult = tl::expected<std::true_type, PropertyError>;

class AbstractCommand
{
public:
	virtual ~AbstractCommand() = default;

	virtual CommandResult execute() = 0;
};

using AbstractCommandPtr = std::shared_ptr<AbstractCommand>;

}  // namespace otg