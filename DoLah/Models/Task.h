#pragma once
#include <string>
#include <chrono>


namespace DoLah {

    /// Task class is a task. It is also referred as floating task.
    /** A floating task is a task without any time specified. */
    class Task {
    public:
        Task(); ///< default constructor
        virtual ~Task(); ///< destructor
        void setId(int id); ///< set the Task ID
        int getId(); ///< get the Task ID
        void setName(std::string); ///< set the Task name
        std::string getName(); ///< get the Task name
        void setDescription(std::string); ///< set the Task description
        std::string getDescription(); ///< get the Task description
        void setDone(bool); ///< set the Task done flag
        bool isDone(); ///< get the Task done flag
    private:
        std::string description; ///< A Detailed explanation about the task.
        std::string name; ///< Task name is the header of the task.
        int id; ///< Task identifier is used for the storage tracking.
        bool done; ///< a flag that mark whether a task has finished, and may be hide or cleared later.
    };

    /// EventTask is a Task that have a specific starting datetime and ending datetime.
    class EventTask : Task {
    public:
        EventTask(); ///< default constructor
        ~EventTask(); ///< destructor
        std::chrono::system_clock::time_point getStartDate(); ///< get the starting datetime
        void setStartDate(std::chrono::system_clock::time_point); ///< set the starting datetime
        std::chrono::system_clock::time_point getEndDate(); ///< get the ending datetime
        void setEndDate(std::chrono::system_clock::time_point); ///< set the ending datetime
    private:
        std::chrono::system_clock::time_point startDate; ///< Task starting datetime
        std::chrono::system_clock::time_point endDate; ///< Task ending datetime
    };

    /// DeadlineTask is a task that have a specific due datetime.
    class DeadlineTask : Task {
    public:
        DeadlineTask(); ///< default constructor
        ~DeadlineTask(); ///< destructor
        std::chrono::system_clock::time_point getDueDate(); ///< get the due date
        void setDueDate(std::chrono::system_clock::time_point); ///< set the due date

    private:
        std::chrono::system_clock::time_point dueDate; ///< Task due datetime
    };
}

using DoLah::Task;
using DoLah::EventTask;