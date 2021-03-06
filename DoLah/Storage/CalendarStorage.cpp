#include "Storage/CalendarStorage.h"
#include "Models/Task.h"
#include <ctime>
#include <iostream>
#include <time.h>
//#include <boost/filesystem.hpp>


namespace DoLah {
    CalendarStorage::CalendarStorage()
    {
    }


    CalendarStorage::~CalendarStorage()
    {
    }

    void CalendarStorage::save(const DoLah::Calendar& calendar, const std::string & filename) {
        std::vector<DoLah::AbstractTask*> taskList = calendar.getAllTaskList();
        YAML::Emitter out;



        YAML::Node todoNode;
        YAML::Node completedNode;

        for (auto it = taskList.begin(); it != taskList.end(); it++) {
            YAML::Node taskNode;
            taskNode["task"] = (*it)->getName();
            taskNode["description"] = (*it)->getDescription();
            if (!(*it)->getTags().empty()) {
                taskNode["tags"] = (*it)->getTags();
            }

            DoLah::FloatingTask* floatingTask = dynamic_cast<DoLah::FloatingTask*>(*it);
            DoLah::EventTask* eventTask = dynamic_cast<DoLah::EventTask*>(*it);
            DoLah::DeadlineTask* deadlineTask = dynamic_cast<DoLah::DeadlineTask*>(*it);

            if (eventTask != NULL) {
                taskNode["start"] = eventTask->getStartDate();
                taskNode["end"] = eventTask->getEndDate();
            }

            if (deadlineTask != NULL) {
                taskNode["due"] = deadlineTask->getDueDate();
            }

            if ((*it)->isDone()) {
                completedNode.push_back(taskNode);
            } else {
                todoNode.push_back(taskNode);
            }
        }

        out << YAML::BeginDoc;
        out << YAML::BeginMap;
        out << YAML::Key << "todo";

        out << YAML::Comment("Todo Tasks");
        out << YAML::Value << todoNode;
        out << YAML::Key << "done";
        out << YAML::Comment("Completed Tasks");
        out << YAML::Value << completedNode;
        out << YAML::EndMap;
        out << YAML::EndDoc;

        std::ofstream ofstream(filename);
        if (ofstream.is_open()) {
            ofstream << out.c_str();
        }
        ofstream.close();
    }

    Calendar CalendarStorage::load(const std::string& filename) {
        Calendar calendar;
        if (!std::ifstream(filename)) {
            std::ofstream out(filename);
            out.close();
        }
        YAML::Node node = YAML::LoadFile(filename);

        if (node.IsMap()) {
            for (auto taskGroupIterator = node.begin(); taskGroupIterator != node.end(); ++taskGroupIterator) {
                std::string taskStatus = taskGroupIterator->first.as<std::string>();

                for (auto taskIterator = taskGroupIterator->second.begin(); taskIterator != taskGroupIterator->second.end(); ++taskIterator) {                    
                    YAML::Node taskNode = *taskIterator;
                    const std::string text;
                    DoLah::AbstractTask* task = NULL;
                    if (taskNode["due"].IsDefined()) {
                        DeadlineTask* d_task = new DeadlineTask;
                        d_task->setDueDate(taskNode["due"].as<std::tm>());
                        task = d_task;
                    } else if (taskNode["start"].IsDefined() && taskNode["end"].IsDefined()) {
                        EventTask* e_task = new EventTask;
                        e_task->setStartDate(taskNode["start"].as<std::tm>());
                        e_task->setEndDate(taskNode["end"].as<std::tm>());
                        task = e_task;
                    } else {
                        task = new FloatingTask;
                    }

                    if (taskStatus == "todo") {
                        task->setDone(false);
                    } else if (taskStatus == "done") {
                        task->setDone(true);
                    }
                    task->setName(taskNode["task"].as<std::string>());
                    task->setDescription(taskNode["description"].as<std::string>());
                    calendar.addTask(task);
                }
            }
        }
        return calendar;
        
    }
}
