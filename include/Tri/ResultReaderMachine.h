// finite state machine for reading "false" or "true" from string

#pragma once

#include "Tri/FiniteState.h"

#include <optional>
#include <string>

// States and events
struct ResultReaderEnums
{
    enum class States : size_t
    {
        start,
        f,
        a,
        l,
        s,
        e, // false
        t,
        r,
        u, // true
        error,
        stop,
        count
    };

    enum class Events : size_t
    {
        first,
        f = first,
        a,
        l,
        s,
        e, // false
        t,
        r,
        u, // true
        stop,
        unknown,
        count
    };
};

// finite state machine for reading "false" or "true" from string
class ResultReaderMachine : public FiniteState<ResultReaderMachine, ResultReaderEnums>
{

public:
    using Base = FiniteState<ResultReaderMachine, ResultReaderEnums>;

    // start function
    void execute(const std::string& str);

    // state machine staff:
    // generates event
    static Events toEvent(const char c);

    // action on transmition to state
    ActionResult add();
    ActionResult toBool();
    ActionResult error();
    std::optional<bool> getExpectedResult() const;

    // whether the result is full
    bool isResultFull() const;

    // Fills States Table
    static StatesTable fillStatesTable();

private:
    size_t m_pos = 0;
    char m_c = 0;
    std::string m_result;
};
