// very simple test framework
#pragma once

#include <string>
#include <vector>

#include <typeinfo>

namespace Tests
{

// Test case interface
struct ITestCase
{
    virtual ~ITestCase() = default;
    virtual bool run() const = 0;
    virtual std::string getName() const = 0;
};

// Test cases collection
class TestCasesCollection
{
public:
    static bool runTests();
    static void add(const ITestCase& testCase);

private:
    inline static std::vector<const ITestCase*> testFuncs{};
};

// Base implementation for test case
// Derived - class which inherits it
//
// declare:
// struct SomeTest : public TestCaseImpl<SomeTest>
// {
//   run() const final {...}
// };
//
// add to test collection somewhere in cpp:
// const SomeTest addToTestsSomeTestImpl;

template <typename Derived>
struct TestCaseImpl : public ITestCase
{
public:
    // tests framework staff
    std::string getName() const final { return m_name; }

protected:
    TestCaseImpl()
        : m_name(typeid(Derived).name())
    {
        TestCasesCollection::add(*static_cast<Derived*>(this));
    }

protected:
    std::string m_name;
};

} // namespace Tests
