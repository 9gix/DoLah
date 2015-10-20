#include "stdafx.h"
#include "CppUnitTest.h"

#include "Models/Task.h"
#include "Commands/Command.h"
#include "Models/Calendar.h"
#include "CalendarBuilder.h"
#include "TaskBuilder.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DoLahTest
{		
	TEST_CLASS(CALENDAR_TESTER) {
	private:

    public:
        TEST_METHOD(AddTask) {
            //Arrange
            DoLah::Calendar testCal = DoLah::Calendar();
            DoLah::FloatingTask* task = TaskBuilder::buildFloatingTask();

            //Act
            testCal.addTask(task);

            //Assert
            Assert::AreEqual(testCal.getTaskList().size(), (size_t) 1); 
            Assert::AreEqual(testCal.getTaskList()[0]->getName(), task->getName());
            Assert::AreEqual(testCal.getTaskList()[0]->getDescription(), task->getDescription());
        }

        TEST_METHOD(DeleteTask) {
            //Arrange
            DoLah::Calendar testCal = CalendarBuilder::buildSimpleCalendar();
            int oldLength = testCal.getTaskList().size();

            //Act
            testCal.deleteTask(4);

            //Assert
            Assert::AreEqual(testCal.getTaskList().size(), (size_t) oldLength - 1);
        }

        TEST_METHOD(SetDoneTask) {
            // Arrange
            DoLah::Calendar cal;
            DoLah::AbstractTask * task = TaskBuilder::buildFloatingTask();
            task->setDone(false);
            cal.addTask(task);
            assert(cal.getTask(0)->isDone() == false);

            // Act
            cal.setDoneTask(0);

            // Assert
            Assert::IsTrue(cal.getDone(0)->isDone());
            Assert::IsTrue(cal.getTaskList().empty());
        }

        TEST_METHOD(SetUnDoneTask) {
            // Arrange
            DoLah::Calendar cal;
            DoLah::AbstractTask * task = TaskBuilder::buildFloatingTask();
            task->setDone(true);
            cal.addTask(task);
            assert(cal.getDone(0)->isDone() == true);

            // Act
            cal.setDoneTask(0, false);

            // Assert
            Assert::IsFalse(cal.getTask(0)->isDone());
            Assert::IsTrue(cal.getDoneList().empty());
        }

        TEST_METHOD(EditTask) {
            //Arrange
            DoLah::Calendar testCal = CalendarBuilder::buildSimpleCalendar();
            DoLah::DeadlineTask* task = TaskBuilder::buildDeadlineTask();

            //Act
            testCal.updateTask(0, task);

            //Assert
            Assert::AreEqual(testCal.getTaskList()[0]->getName(), task->getName());
            Assert::AreEqual(testCal.getTaskList()[0]->getDescription(), task->getDescription());
            Assert::AreEqual(testCal.getTaskList()[0]->isDone(), task->isDone());
        }

		TEST_METHOD(ClearTask) {
            //Arrange
            DoLah::Calendar testCal = CalendarBuilder::buildSimpleCalendar();
			
            //Act
            testCal.clearTasks();
			
            //Assert
            Assert::IsTrue(testCal.getTaskList().empty());
		}

		TEST_METHOD(FindTaskThatExists) {
			//Arrange
            DoLah::Calendar testCal = CalendarBuilder::buildSimpleCalendar();

            //Act
            std::vector<DoLah::AbstractTask*> resultVector = testCal.search("Floating");

            //Assert
            Assert::AreEqual(resultVector.size(), (size_t) 5);
		}

        TEST_METHOD(FindTaskThatDoesNotExist) {
            //Arrange
            DoLah::Calendar testCal = CalendarBuilder::buildSimpleCalendar();

            //Act
            std::vector<DoLah::AbstractTask*> resultVector = testCal.search("The quick brown fox");

            //Assert
            Assert::AreEqual(resultVector.size(), (size_t)0);
        }
	};
}