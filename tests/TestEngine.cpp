#include "TestEngine.h"

#include <iostream>
#include <string>

namespace
{
struct ScopedMsg
{
    ScopedMsg(const std::string& m)
        : message(m)
    {
        std::cout << '\t' << message << " {\n";
    }
    ~ScopedMsg() { std::cout << '\t' << message << " }\n"; }

    const std::string message;
};
} // namespace

namespace Tests
{
void TestCasesCollection::add(const ITestCase& testCase)
{
    testFuncs.push_back(&testCase);
}

bool TestCasesCollection::runTests()
{
    std::cout << testFuncs.size() << " tests to run:\n";
    size_t faledCount = 0;
    for (const auto& f : testFuncs)
    {
        ScopedMsg scopedMsg(f->getName());
        if (!f->run())
        {
            std::cout << "\tTest : " << f->getName() << " failed!\n";
            ++faledCount;
        }
    }

    if (faledCount)
    {
        std::cout << faledCount << " tests failed\n";
    }
    else
    {
        std::cout << "SUCCESS!\n";
    }
    return true;
}

} // namespace Tests
