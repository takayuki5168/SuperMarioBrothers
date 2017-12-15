#pragma once

#include <vector>
#include "include/abst_object.hpp"

class AbstEnemy : public AbstObject
{
public:
    AbstEnemy(int x, int y, int w, int h, int color, std::string name)
        : AbstObject(x, y, w, h, color, name)
    {
        m_gravity = 0.1;
    }

private:
};
