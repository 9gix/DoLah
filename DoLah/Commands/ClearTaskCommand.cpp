#include "Command.h"

namespace DoLah {
	//public
	ClearTaskCommand::ClearTaskCommand() {

	}

	ClearTaskCommand::~ClearTaskCommand() {

	}

	void ClearTaskCommand::execute() {
		this->calendar.clearTasks();
	}

	//private
}