#include "CommandStop.h"

#include "../types/ExceptionError.h"

namespace otg {

Result<void> CommandStop::execute()
{
	return makeUnexpected(ExceptionErrorType::ExecuteStop, "Stop execute commands");
}

}  // namespace otg