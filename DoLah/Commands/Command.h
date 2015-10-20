#pragma once

#include <vector>
#include <string>
#include "Models/Task.h"
#include "Models/Calendar.h"

namespace DoLah {

	class ITaskCommand {
	public:
		virtual ~ITaskCommand() = 0;
        void setCalendar(DoLah::Calendar*);
		virtual void execute() = 0;

    protected:
        DoLah::Calendar* calendar;
	};

	class AddTaskCommand : public ITaskCommand {
	public:
		AddTaskCommand();
		AddTaskCommand(DoLah::AbstractTask*);
		~AddTaskCommand();

		void execute();

	private:
		DoLah::AbstractTask* task;
	};

	class EditTaskCommand : public ITaskCommand {
	public:
		EditTaskCommand();
		EditTaskCommand(int, DoLah::AbstractTask *);
		~EditTaskCommand();
		void execute();

	private:
		int taskIndex;
		DoLah::AbstractTask* task;
	};

	class DeleteTaskCommand : public ITaskCommand {
	public:
		DeleteTaskCommand();
		DeleteTaskCommand(int);
		~DeleteTaskCommand();

		void execute();

	private:
		int taskIndex;
	};

	class ClearTaskCommand : public ITaskCommand {
	public:
		ClearTaskCommand();
		~ClearTaskCommand();

		void execute();
	};

	class SearchTaskCommand : public ITaskCommand {
	public:
		SearchTaskCommand();
        SearchTaskCommand(std::string);
		SearchTaskCommand(std::string, std::vector<AbstractTask*> *);
		~SearchTaskCommand();

        std::vector<AbstractTask*> getResultVector();

        void setResultVector(std::vector<AbstractTask*>*);

		void execute();

	private:
		std::string query;
        std::vector<AbstractTask*> ** resultVector;
	};

	class UndoTaskCommand : public ITaskCommand {
	public:
		UndoTaskCommand();
		~UndoTaskCommand();

		void execute();
	};

	class RedoTaskCommand : public ITaskCommand {
	public:
		RedoTaskCommand();
		~RedoTaskCommand();

		void execute();
	};

}