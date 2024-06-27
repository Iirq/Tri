#include "TestEngine.h"

#include <iostream>
#include <functional>

int main(int ac, char* argv[])
{
    try
    {
        return Tests::TestCasesCollection::runTests() ? 0 : 1;
    }
    catch (const std::exception& e)
    {
        std::cout << e.what();
    }
    return 1;
}
