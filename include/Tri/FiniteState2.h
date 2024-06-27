#pragma once

#include <vector>
#include <array>

template <typename T, typename Enum>
class Array
{
public:
    enum
    {
        Dim = Enum::count
    };

    template <typename... Args>
    Array(Args&&... args)
        : m_array(std::forward<Args>(args)...){};

    T& operator[](Enum i) { return m_array[static_cast<size_t>(i)]; }
    const T& operator[](Enum i) const { return m_array[static_cast<size_t>(i)]; }

private:
    std::array<T, Dim> m_array;
};

template <typename Derived>
class DerivedThis
{
protected:
    using TDerived = Derived;
    Derived* derivedThis() { return static_cast<Derived*>(this); }
    const Derived* derivedThis() const { return static_cast<const Derived*>(this); }
};

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

template <typename Derived, typename StatesEnum, typename EventsEnum>
class FiniteState : public DerivedThis<Derived>, public FiniteStateEnums
{
    using Inherited = DerivedThis<Derived>;

public:
    using Action = ActionResult (Derived::*)(void);
    using States = StatesEnum;
    using Events = EventsEnum;

    struct Transition
    {
        States target;
        Action action;
    };

    void set(States current, Events e, const Transition& tr) { m_statesTable[current][e] = tr; }
    const Transition& getTransition(Events e) const
    {
        const TransitionByEvents& transitionByEvents = m_statesTable[m_currentState];
        return transitionByEvents[e];
    }

    ActionResult treat(Events e)
    {
        const Transition& target = getTransition(e);
        ActionResult actionResult = std::invoke(target.action, Inherited::derivedThis());
        if (actionResult == ActionResult::handled)
        {
            m_currentState = target.target;
        }

        return actionResult;
    }

    CompletionStatus getCompletionStatus() const { return m_completionStatus; }

protected:
    FiniteState(States currentState = Derived::States::start)
        : m_currentState(currentState)
        , m_statesTable{}
    {
        for (States state = States::start; state < States::count; state = inc(state))
        {
            for (Events e = Events::first; e < Events::count; e = inc(e))
            {
                set(state, e, {States::error, &Derived::error});
            }
        }
    };

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

private:
    States inc(States v)
    {
        size_t i = static_cast<size_t>(v);
        return static_cast<States>(i + 1);
    }
    Events inc(Events v)
    {
        size_t i = static_cast<size_t>(v);
        return static_cast<Events>(i + 1);
    }

protected:
    using TransitionByEvents = Array<Transition, Events>;
    using StatesTable = Array<TransitionByEvents, States>;

    States m_currentState;
    CompletionStatus m_completionStatus = CompletionStatus::unFinished;

    // TODO: move it to static data
    StatesTable m_statesTable;
};
