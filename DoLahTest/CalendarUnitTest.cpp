#include "stdafx.h"
#include "CppUnitTest.h"

#include "Models/Task.h"
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
            Assert::AreEqual((size_t)1, testCal.getTaskList().size());
            Assert::AreEqual(task->getName(), testCal.getTaskList()[0]->getName());
            Assert::AreEqual(task->getDescription(), testCal.getTaskList()[0]->getDescription());
        }

        TEST_METHOD(DeleteTask) {
            //Arrange
            DoLah::Calendar testCal = CalendarBuilder::buildSimpleCalendar();
            int oldLength = testCal.getTaskList().size();

            //Act
            testCal.deleteTask(4);

            //Assert
            Assert::AreEqual((size_t)oldLength - 1, testCal.getTaskList().size());
        }

        // TESTING FOR BOUNDARY CASE WHERE TASK TO BE DELETED DOES NOT EXIST
        TEST_METHOD(DeleteTaskOutOfRange) {
            //Arrange
            DoLah::Calendar testCal = CalendarBuilder::buildSimpleCalendar();
            int Length = testCal.getTaskList().size();

            //Act
            std::function<void(void)> func = [&testCal, Length] {
                testCal.deleteTask(Length + 2);
            };
            //Assert
            Assert::ExpectException<std::out_of_range>(func);
            Assert::AreEqual((size_t)Length, testCal.getTaskList().size());
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
            Assert::AreEqual(task->getName(), testCal.getTaskList()[0]->getName());
            Assert::AreEqual(task->getDescription(), testCal.getTaskList()[0]->getDescription());
            Assert::AreEqual(task->isDone(), testCal.getTaskList()[0]->isDone());
        }

        // TESTING FOR BOUNDARY CASE WHERE TASK TO BE EDITED DOES NOT EXIST
        TEST_METHOD(EditTaskOutOfRange) {
            //Arrange
            DoLah::Calendar testCal = CalendarBuilder::buildSimpleCalendar();
            DoLah::DeadlineTask* task = TaskBuilder::buildDeadlineTask();

            //Act
            std::function<void(void)> func = [&testCal, task] {
                testCal.updateTask(-1, task);
            };
            //Assert
            Assert::ExpectException<std::out_of_range>(func);
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
            Assert::AreEqual((size_t)5, resultVector.size());
		}

        TEST_METHOD(FindTaskThatDoesNotExist) {
            //Arrange
            DoLah::Calendar testCal = CalendarBuilder::buildSimpleCalendar();

            //Act
            std::vector<DoLah::AbstractTask*> resultVector = testCal.search("The quick brown fox");

            //Assert
            Assert::AreEqual((size_t)0, resultVector.size());
        }
	};
}