#include "Tri/RunTasksFile.h"
#include "Tri/TasksExecutor.h"

#include <fstream>

namespace
{
std::string toString(bool v)
{
    return (v ? "true" : "false");
}
void report(const TaskExecutor& taskExecutor, size_t& totalTasks, size_t& failedTasks)
{
    const Task& task = taskExecutor.getTask();
    const bool result = taskExecutor.getResult() ? *taskExecutor.getResult() : false;

    const bool expectedResult = task.getExpectedResult();

    if (result != expectedResult)
    {
        std::cout << "line " << taskExecutor.getLineNumber() << ": expected " << toString(expectedResult) << ", got "
                  << toString(result) << ".\n";
    }
    if (result != task.getExpectedResult())
    {
        ++failedTasks;
    }
    ++totalTasks;
}
} // namespace

void execute(const std::filesystem::path& filePath)
{
    std::string line;
    std::ifstream rfile(filePath);
    if (!rfile.is_open()) std::cout << "can't open file : " << filePath.string() << '\n';

    size_t totalTasks{};
    size_t failedTasks{};
    TaskExecutor taskExecutor;
    while (!rfile.eof())
    {
        taskExecutor.execute(rfile);
        report(taskExecutor, totalTasks, failedTasks);
    }

    std::cout << "Tests done " << totalTasks << '/' << failedTasks << " failed.\n";
}
