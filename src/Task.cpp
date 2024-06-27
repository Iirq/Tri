#include "Tri/Task.h"
#include "Tri/Intersections.h"

bool Task::execute()
{
    bool intersects = doesIntersect(m_tr1, m_tr2);
    return intersects == m_expectedResult;
}
