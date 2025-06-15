#include "CommandInterrupt.h"

#include "types/ExceptionError.h"

namespace otg {

Result<void> CommandInterrupt::execute()
{
	return makeUnexpected(ExceptionErrorType::ExecuteInterrupt, "Interrupt execute commands");
}

}  // namespace otg