#include "Tri/RunTasksFile.h"

#include <iostream>

int main(int ac, char* argv[])
{
    if (ac < 2)
    {
        std::cout << "to few options\n";
        return 1;
    }

    try
    {
        execute(argv[1]);
        return 0;
    }
    catch (const std::exception& e)
    {
        std::cout << e.what();
        return 1;
    }
}
