#pragma once

#include <cmath>
#include <limits>

// comparision of floats according to https://en.cppreference.com/w/cpp/types/numeric_limits/epsilon
// eps = std::numeric_limits<T>::epsilon() is the smallest value for which 1.0 and 1.0 +/- eps differs
// So to compare 2.0 and 3.0 this eps must be multiplyed by max(2.0,3.0) or (2.0 + 3.0)
// because 2.0 and 2.0 + std::numeric_limits<T>::epsilon() are the same from compilator point of view

template <class T>
typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type isNear(T x, T y)
{
    // the machine epsilon has to be scaled to the magnitude of the values used
    return std::abs(x - y) <= std::numeric_limits<T>::epsilon() * std::abs(x + y);
}

template <class T>
typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type isNear(T x, T y, int ulp)
{
    // the machine epsilon has to be scaled to the magnitude of the values used
    // and multiplied by the desired precision in ULPs (units in the last place)
    return std::abs(x - y) <= std::numeric_limits<T>::epsilon() * std::abs(x + y) * ulp;
}

// simple float comparision with given epsilon
template <class T, class E = double>
typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type isNear(T x, T y, const E epsilon)
{
    // the simple epsilon defference comparision
    return std::abs(x - y) <= epsilon;
}

template <class T, class E = double>
typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type isLess(T x, T y, const E epsilon)
{
    // the simple epsilon defference comparision
    return x - epsilon < y;
}

template <class T, class E = double>
typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type isLess0(T x, const E epsilon)
{
    return isLess(x, T{}, epsilon);
}
