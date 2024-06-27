#include "Tri/ResultReaderMachine.h"

#include <iostream>

void ResultReaderMachine::execute(const std::string& str)
{
    m_pos = 0;
    m_c = 0;
    m_result.clear();

    for (size_t i = 0; i < str.size() && getCompletionStatus() == CompletionStatus::unFinished; ++i, ++m_pos)
    {
        m_c = str[i];
        Events e = toEvent(m_c);
        treat(e);
    }
    treat(Events::stop);
}

ResultReaderMachine::Events ResultReaderMachine::toEvent(const char c)
{
    switch (c)
    {
        case 'f':
            return Events::f;
        case 'a':
            return Events::a;
        case 'l':
            return Events::l;
        case 's':
            return Events::s;
        case 'e':
            return Events::e;
        case 't':
            return Events::t;
        case 'r':
            return Events::r;
        case 'u':
            return Events::u;
        default:
            return Events::unknown;
    }
}

ResultReaderMachine::ActionResult ResultReaderMachine::add()
{
    m_result += m_c;
    return ActionResult::handled;
}
ResultReaderMachine::ActionResult ResultReaderMachine::toBool()
{
    if (isResultFull()) return success();
    return error();
}
ResultReaderMachine::ActionResult ResultReaderMachine::error()
{
    std::string errorPlace(1, m_c);
    std::cout << "pos " << m_pos << ": error in char: " << errorPlace << '\n';
    return failure();
}

std::optional<bool> ResultReaderMachine::getExpectedResult() const
{
    if (isResultFull()) return m_result == "true";
    return {};
}

bool ResultReaderMachine::isResultFull() const
{
    return (m_result == "true" || m_result == "false");
}

ResultReaderMachine::StatesTable ResultReaderMachine::fillStatesTable()
{
    ResultReaderMachine::StatesTable t;
    t.set(States::start, Events::f, {States::f, &ResultReaderMachine::add});
    t.set(States::f, Events::a, {States::a, &ResultReaderMachine::add});
    t.set(States::a, Events::l, {States::l, &ResultReaderMachine::add});
    t.set(States::l, Events::s, {States::s, &ResultReaderMachine::add});
    t.set(States::s, Events::e, {States::e, &ResultReaderMachine::add});
    t.set(States::start, Events::t, {States::t, &ResultReaderMachine::add});
    t.set(States::t, Events::r, {States::r, &ResultReaderMachine::add});
    t.set(States::r, Events::u, {States::u, &ResultReaderMachine::add});
    t.set(States::u, Events::e, {States::e, &ResultReaderMachine::add});
    t.set(States::e, Events::stop, {States::stop, &ResultReaderMachine::toBool});
    return t;
}

ResultReaderMachine::StatesTable ResultReaderMachine::Base::m_statesTable = ResultReaderMachine::fillStatesTable();
