#pragma once

#include <vector>
#include <array>

// to operate with std::array through enums
template <typename T, typename Enum>
class EnumArray
{
public:
    enum
    {
        Dim = Enum::count
    };

    template <typename... Args>
    EnumArray(Args&&... args)
        : m_array(std::forward<Args>(args)...){};

    T& operator[](Enum i) { return m_array[static_cast<size_t>(i)]; }
    const T& operator[](Enum i) const { return m_array[static_cast<size_t>(i)]; }

private:
    std::array<T, Dim> m_array;
};
