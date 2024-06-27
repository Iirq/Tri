#include "Tri/RunTasksFile.h"
#include "Tri/TasksExecutor.h"

#include <fstream>

void execute(const std::filesystem::path& filePath)
{
    std::string line;
    std::ifstream rfile(filePath);
    if (!rfile.is_open()) std::cout << "can't open file : " << filePath.string() << '\n';

    TaskExecutor taskExecutor;
    taskExecutor.execute(rfile);
}
