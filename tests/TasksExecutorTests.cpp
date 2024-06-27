#include "TestEngine.h"

#include "Tri/ReadTriangle.h"
#include "Tri/ResultReaderMachine.h"
#include "Tri/TasksExecutor.h"

#include "Tri/Defs.h"
#include "Tri/Vector3d.h"

#include <sstream>

namespace Tests
{
namespace
{

struct ReadPoint : public TestCaseImpl<ReadPoint>
{
    bool run() const final
    {
        {
            std::istringstream str("");
            auto it = std::istream_iterator<double>(str);
            auto point = readPoint(it);
            if (point) return false;
        }
        {
            std::istringstream str("1");
            auto it = std::istream_iterator<double>(str);
            auto point = readPoint(it);
            if (point) return false;
        }
        {
            std::istringstream str("1 a");
            auto it = std::istream_iterator<double>(str);
            auto point = readPoint(it);
            if (point) return false;
        }
        {
            std::istringstream str("1 1 a");
            auto it = std::istream_iterator<double>(str);
            auto point = readPoint(it);
            if (point) return false;
        }
        {
            std::istringstream str("1 1 1");
            auto it = std::istream_iterator<double>(str);
            auto point = readPoint(it);
            if (!point) return false;
            if (!isNear(*point, Point3d(1, 1, 1), Tolerance)) return false;
        }
        {
            std::istringstream str("1 1 1 1");
            auto it = std::istream_iterator<double>(str);
            auto point = readPoint(it);
            if (!point) return false;
            if (!isNear(*point, Point3d(1, 1, 1), Tolerance)) return false;
        }
        {
            std::istringstream str("123 1 1");
            auto it = std::istream_iterator<double>(str);
            auto point = readPoint(it);
            if (!point) return false;
            if (!isNear(*point, Point3d(123, 1, 1), Tolerance)) return false;
        }
        {
            std::istringstream str("1 123 1 1");
            auto it = std::istream_iterator<double>(str);
            auto point = readPoint(it);
            if (!point) return false;
            if (!isNear(*point, Point3d(1, 123, 1), Tolerance)) return false;
        }
        return true;
    }
};
static const ReadPoint addToTestsReadPoint;

struct ReadTriangle : public TestCaseImpl<ReadTriangle>
{
    bool run() const final
    {
        {
            std::string str("");
            auto triangle = readTriangle(str);
            if (triangle) return false;
        }
        {
            std::string str("1 1 1 a");
            auto triangle = readTriangle(str);
            if (triangle) return false;
        }
        {
            std::string str("1 1 1 2 2 2 a");
            auto triangle = readTriangle(str);
            if (triangle) return false;
        }
        {
            std::string str("1 1 a 1 2 2 2 a");
            auto triangle = readTriangle(str);
            if (triangle) return false;
        }
        {
            std::string str("1 1 1 2 2 2 3 3 3");
            auto triangle = readTriangle(str);

            Triangle t({Point3d{1, 1, 1}, Point3d{2, 2, 2}, Point3d{3, 3, 3}});
            if (!triangle || !isNear(*triangle, t, Tolerance)) return false;
        }
        {
            std::string str("1 1 1 2 2 2 3 3 3 a");
            auto triangle = readTriangle(str);
            if (!triangle) return false;
        }
        {
            std::string str(" 0 0 0 10 0 0 0 10 0");
            auto triangle = readTriangle(str);
            if (!triangle) return false;
        }
        return true;
    }
};
static const ReadTriangle addToTestsReadTriangle;

struct ResultReaderMachineTestsFalse : public TestCaseImpl<ResultReaderMachineTestsFalse>
{
    bool run() const final
    {
        {
            std::string str = "fal";
            ResultReaderMachine resultReaderMachine;
            resultReaderMachine.execute(str);
            if (resultReaderMachine.getCompletionStatus() == TaskExecutor::CompletionStatus::success) return false;
        }
        {
            std::string str = "false";
            ResultReaderMachine resultReaderMachine;
            resultReaderMachine.execute(str);
            if (resultReaderMachine.getCompletionStatus() != TaskExecutor::CompletionStatus::success) return false;
        }
        return true;
    }
};
static const ResultReaderMachineTestsFalse addToTestsReaderMachineTestsFalse;

struct ResultReaderMachineTestsTrue : public TestCaseImpl<ResultReaderMachineTestsTrue>
{
    bool run() const final
    {
        {
            std::string str = "tr";
            ResultReaderMachine resultReaderMachine;
            resultReaderMachine.execute(str);
            if (resultReaderMachine.getCompletionStatus() == TaskExecutor::CompletionStatus::success) return false;
        }
        {
            std::string str = "true";
            ResultReaderMachine resultReaderMachine;
            resultReaderMachine.execute(str);
            if (resultReaderMachine.getCompletionStatus() != TaskExecutor::CompletionStatus::success) return false;
        }
        return true;
    }
};
static const ResultReaderMachineTestsTrue addToTestsReaderMachineTestsTrue;

struct TasksExecutorSuccessTests : public TestCaseImpl<TasksExecutorSuccessTests>
{
    bool run() const final
    {
        {
            std::string input("#this is a comment\n"
                              "0 0 0 1 0 0 0 1 0\n"
                              "0 0 0 1 0 0 0 1 0\n"
                              "true");
            std::istringstream istr(input);
            TaskExecutor taskExecutor;
            taskExecutor.execute(istr);
            if (taskExecutor.getCompletionStatus() != TaskExecutor::CompletionStatus::success) return false;
        }
        {
            std::string input("0 0 0 1 0 0 0 1 0\n"
                              "#this is a comment\n"
                              "0 0 0 1 0 0 0 1 0\n"
                              "true");
            std::istringstream istr(input);
            TaskExecutor taskExecutor;
            taskExecutor.execute(istr);
            if (taskExecutor.getCompletionStatus() != TaskExecutor::CompletionStatus::success) return false;
        }
        return true;
    }
};
static const TasksExecutorSuccessTests addToTestsExecutorSuccessTests;

struct TasksExecutorFirstPointFailureTests : public TestCaseImpl<TasksExecutorFirstPointFailureTests>
{
    bool run() const final
    {
        {
            std::string input("a 0 0 1 0 0 0 1 0\n"
                              "#this is a comment\n"
                              "0 0 0 1 0 0 0 1 0\n"
                              "true");
            std::istringstream istr(input);
            TaskExecutor taskExecutor;
            taskExecutor.execute(istr);
            if (taskExecutor.getCompletionStatus() == TaskExecutor::CompletionStatus::success) return false;
        }
        {
            std::string input("0 0 0 1 0 0 0 1 0\n"
                              "#this is a comment\n"
                              "a 0 0 1 0 0 0 1 0\n"
                              "true");
            std::istringstream istr(input);
            TaskExecutor taskExecutor;
            taskExecutor.execute(istr);
            if (taskExecutor.getCompletionStatus() == TaskExecutor::CompletionStatus::success) return false;
        }
        return true;
    }
};
static const TasksExecutorFirstPointFailureTests addToTestsExecutorFirstPointFailureTests;

struct TasksExecutorMultiTaskTests : public TestCaseImpl<TasksExecutorMultiTaskTests>
{
    bool run() const final
    {
        std::string input("1 0 0 1 0 0 0 1 0\n"
                          "1 0 0 1 0 0 0 1 0\n"
                          "true\n"
                          "2 0 0 1 0 0 0 1 0\n"
                          "2 0 0 1 0 0 0 1 0\n"
                          "true\n"
                          "3 0 0 1 0 0 0 1 0\n"
                          "3 0 0 1 0 0 0 1 0\n"
                          "true");
        std::istringstream istr(input);

        size_t lineNumber = 0;
        while (!istr.eof())
        {
            TaskExecutor taskExecutor;
            taskExecutor.setLineNumber(lineNumber);
            taskExecutor.execute(istr);
            lineNumber = taskExecutor.getLineNumber();
            if (taskExecutor.getCompletionStatus() != TaskExecutor::CompletionStatus::success) return false;
        }
        return true;
    }
};
static const TasksExecutorMultiTaskTests addToTestsTasksExecutorMultiTaskTests;
} // namespace
} // namespace Tests
