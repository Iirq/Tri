// Finite States Machine implementation
#pragma once

#include "Tri/DerivedThis.h"
#include "Tri/EnumArray.h"

#include <vector>

// States table
//
// TProcessor - state machine providing transmition actions
// ActionResultEnum - TProcessor::action returns ActionResultEnum
// Enums - enums for states and events
// must includes enum States and enum Events
// Enums::States has to provide : start, error, count
// Enums::Events has to provide : first, Events::count
// enums must go concecutevly to provide possibility use ++ operation on them

template <typename TProcessor, typename Enums, typename ActionResultEnum>
class FiniteStateTable
{

public:
    using ActionResult = ActionResultEnum;
    using Processor = TProcessor;
    using Action = ActionResult (Processor::*)(void);
    using States = typename Enums::States;
    using Events = typename Enums::Events;

    struct Transition
    {
        States target;
        Action action;
    };

    void set(States current, Events e, const Transition& tr) { m_statesTable[current][e] = tr; }
    const Transition& getTransition(States state, Events e) const
    {
        const TransitionByEvents& transitionByEvents = m_statesTable[state];
        return transitionByEvents[e];
    }

    FiniteStateTable()
    {
        for (States state = States::start; state < States::count; state = inc(state))
        {
            for (Events e = Events::first; e < Events::count; e = inc(e))
            {
                set(state, e, {States::error, &Processor::error});
            }
        }
    };

private:
    template <typename T>
    static T inc(T v)
    {
        size_t i = static_cast<size_t>(v);
        return static_cast<T>(i + 1);
    }

protected:
    using TransitionByEvents = EnumArray<Transition, Events>;
    using StatesTable = EnumArray<TransitionByEvents, States>;

    StatesTable m_statesTable;
};

// action results and finite state machine completion status
struct FiniteStateEnums
{
    enum class ActionResult
    {
        unProcessed,
        handled
    };
    enum class CompletionStatus
    {
        unFinished,
        success,
        failure,
    };
};

// Finite State Machine base implementation
// Derived - final engine with all action definitions
// Enums - enums for states and events
template <typename Derived, typename Enums>
class FiniteState : public DerivedThis<Derived>, public FiniteStateEnums
{
    using Inherited = DerivedThis<Derived>;

public:
    using StatesTable = FiniteStateTable<Derived, Enums, ActionResult>;
    using Action = typename StatesTable::Action;
    using States = typename StatesTable::States;
    using Events = typename StatesTable::Events;
    using Transition = typename StatesTable::Transition;
    using Processor = typename StatesTable::Processor;

    FiniteState() { start(); }

    void start()
    {
        m_currentState = States::start;
        m_completionStatus = CompletionStatus::unFinished;
    }

    // treat event
    ActionResult treat(Events e)
    {
        const Transition& target = m_statesTable.getTransition(m_currentState, e);
        ActionResult actionResult = std::invoke(target.action, Inherited::derivedThis());
        if (actionResult == ActionResult::handled)
        {
            m_currentState = target.target;
        }

        return actionResult;
    }

    CompletionStatus getCompletionStatus() const { return m_completionStatus; }

    // default actions
    ActionResult empty() { return ActionResult::unProcessed; }
    ActionResult error() { return failure(); }
    ActionResult success()
    {
        m_completionStatus = CompletionStatus::success;
        return ActionResult::handled;
    }
    ActionResult failure()
    {
        m_completionStatus = CompletionStatus::failure;
        return ActionResult::handled;
    }

protected:
    States m_currentState;
    CompletionStatus m_completionStatus;

    static StatesTable m_statesTable;
};
