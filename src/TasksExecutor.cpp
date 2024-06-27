#include "Tri/TasksExecutor.h"
#include "Tri/ReadTriangle.h"
#include "Tri/ResultReaderMachine.h"

#include "Tri/Defs.h"
#include "Tri/Triangle.h"
#include "Tri/Vector3d.h"

#include <fstream>
#include <iostream>

namespace
{
std::string toString(bool v)
{
    return (v ? "true" : "false");
}
} // namespace

TaskExecutor::TaskExecutor(size_t currentLineNumber, const std::string& m_currentLine)
    : Base()
    , m_currentLineNumber(currentLineNumber)
    , m_currentLine(m_currentLine)
{
}

void TasksExecutor::execute(std::istream& istr)
{
    while (!istr.eof())
    {
        TaskExecutor taskExecutor;
        taskExecutor.execute(istr);
    }
}

TaskExecutor::StatesTable TaskExecutor::Base::m_statesTable = TaskExecutor::fillStatesTable();

TaskExecutor::StatesTable TaskExecutor::fillStatesTable()
{
    TaskExecutor::StatesTable t;
    t.set(States::start, Events::sharp, {States::start, &TaskExecutor::empty});
    t.set(States::start, Events::digit, {States::firstPoint, &TaskExecutor::readFirstPoint});

    t.set(States::comment, Events::sharp, {States::start, &TaskExecutor::empty});
    t.set(States::comment, Events::letter, {States::error, &TaskExecutor::empty});
    t.set(States::comment, Events::digit, {States::firstPoint, &TaskExecutor::empty});
    t.set(States::comment, Events::unknown, {States::error, &TaskExecutor::empty});

    t.set(States::firstPoint, Events::sharp, {States::start, &TaskExecutor::empty});
    t.set(States::firstPoint, Events::digit, {States::secondPoint, &TaskExecutor::readSecondPoint});

    t.set(States::secondPoint, Events::sharp, {States::start, &TaskExecutor::empty});
    t.set(States::secondPoint, Events::letter, {States::result, &TaskExecutor::readExpectedResult});

    t.set(States::result, Events::sharp, {States::result, &TaskExecutor::empty});
    t.set(States::result, Events::stop, {States::stop, &TaskExecutor::test});

    return t;
}

TaskExecutor::Events TaskExecutor::toEvent(const std::string& str)
{
    if (str.empty() || str.front() == '\n')
        return Events::sharp;
    else
    {
        char c = str.front();
        if (c == '#')
            return Events::sharp;
        else if (std::isdigit(c))
            return Events::digit;
        else if (std::isalpha(c))
            return Events::letter;
        else
            return Events::unknown;
    }
}

void TaskExecutor::execute(std::istream& istr)
{
    start();
    while (getCompletionStatus() == CompletionStatus::unFinished)
    {
        if (!std::getline(istr, m_currentLine)) break;

        Events e = toEvent(m_currentLine);
        treat(e);
        ++m_currentLineNumber;
    }
}

TaskExecutor::ActionResult TaskExecutor::error()
{
    std::cout << "line " << m_currentLineNumber << ": error in line: " << m_currentLine << '\n';
    return failure();
}

TaskExecutor::ActionResult TaskExecutor::readFirstPoint()
{
    return readPoint(&Task::setTriangle1);
}

TaskExecutor::ActionResult TaskExecutor::readSecondPoint()
{
    return readPoint(&Task::setTriangle2);
}

TaskExecutor::ActionResult TaskExecutor::readExpectedResult()
{
    ResultReaderMachine resultReader;
    resultReader.execute(m_currentLine);
    if (auto expectedResult = resultReader.getExpectedResult();
        resultReader.getCompletionStatus() == CompletionStatus::success && expectedResult)
    {
        m_task.setExpectedResult(*expectedResult);
        return test();
    }

    return failure();
}

TaskExecutor::ActionResult TaskExecutor::test()
{
    m_result = m_task.execute();
    return success();
}

TaskExecutor::ActionResult TaskExecutor::readPoint(void (Task::*setTriangle)(const Triangle&))
{
    if (auto tr = readTriangle(m_currentLine); tr)
    {
        (m_task.*setTriangle)(*tr);
        return ActionResult::handled;
    }
    return failure();
}

void TaskExecutor::setLineNumber(size_t lineNumber)
{
    m_currentLineNumber = lineNumber;
}

size_t TaskExecutor::getLineNumber() const
{
    return m_currentLineNumber;
}
