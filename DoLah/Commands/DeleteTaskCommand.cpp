#include "Command.h"

namespace DoLah {
	//public
	DeleteTaskCommand::DeleteTaskCommand() {

	}

	DeleteTaskCommand::~DeleteTaskCommand() {

	}

	int DeleteTaskCommand::getTargetId() {
		return targetId;
	}

	void DeleteTaskCommand::setTargetId(int id) {
		targetId = id;
	}

	void DeleteTaskCommand::execute() {
		//TODO
	}

	//private
}