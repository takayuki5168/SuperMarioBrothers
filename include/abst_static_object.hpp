#pragma once

#include <vector>
#include "include/abst_object.hpp"

class AbstStaticObject : public AbstObject
{
public:
    explicit AbstStaticObject(int x, int y, int w, int h, int color, std::string name)
        : AbstObject(x, y, w, h, color, name) {}
};
