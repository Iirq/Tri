#pragma once
#include "Tri/Triangle.h"

// Task to execute. Simplest version
class Task
{
public:
    [[nodiscard]] bool execute();
    void setExpectedResult(bool expectedResult) { m_expectedResult = expectedResult; }
    [[nodiscard]] bool getExpectedResult() const { return m_expectedResult; }
    void setTriangle1(const Triangle& tr) { m_tr1 = tr; }
    void setTriangle2(const Triangle& tr) { m_tr2 = tr; }

private:
    bool m_expectedResult;
    Triangle m_tr1;
    Triangle m_tr2;
};
