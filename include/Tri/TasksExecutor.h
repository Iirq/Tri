// finite state machine for reading test case from stream

#pragma once

#include "Tri/FiniteState.h"
#include "Tri/Task.h"

#include <iostream>
#include <optional>
#include <string>

// states & events for finite state machine
// for reading test case from stream
struct TaskExecutorEnums
{
    enum class States : size_t
    {
        start,
        comment,
        firstPoint,
        secondPoint,
        result,
        stop,
        error,
        count
    };

    enum class Events : size_t
    {
        first,
        sharp = first,
        letter,
        digit,
        stop,
        unknown,
        count
    };
};

// finite state machine for reading test case from stream
class TaskExecutor : public FiniteState<TaskExecutor, TaskExecutorEnums>
{
public:
    using Base = FiniteState<TaskExecutor, TaskExecutorEnums>;

    // start function
    void execute(std::istream& istr);

    // state machine staff:
    // generates event
    static Events toEvent(const std::string& str);

    // action on transmition to state
    ActionResult error();
    ActionResult readFirstPoint();
    ActionResult readSecondPoint();
    ActionResult readExpectedResult();
    ActionResult test();

    // whether the test result mathed expected one
    std::optional<bool> getResult() const { return m_result; }

    // Fills States Table
    static StatesTable fillStatesTable();

    // error reporting support
    void setLineNumber(size_t lineNumber);
    size_t getLineNumber() const;

private:
    ActionResult readPoint(void (Task::*setTriangle)(const Triangle&));

private:
    size_t m_currentLineNumber = 0;
    std::string m_currentLine;

    Task m_task;
    std::optional<bool> m_result;
};

// reads from stream end executes multiply tests cases
class TasksExecutor
{
public:
    void execute(std::istream& istr);
};