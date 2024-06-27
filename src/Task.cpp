#include "Tri/Task.h"
#include "Tri/Intersections.h"

bool Task::execute()
{
    return doesIntersect(m_tr1, m_tr2);
}
