#pragma once

// Static strategy implementation
template <typename Derived>
struct DerivedThis
{
    using TDerived = Derived;
    Derived* derivedThis() { return static_cast<Derived*>(this); }
    const Derived* derivedThis() const { return static_cast<const Derived*>(this); }
};
