#pragma once

#include "include/abst_static_object.hpp"

class AbstUniqueObject : public AbstStaticObject
{
public:
    explicit AbstUniqueObject(int x, int y, int w, int h, int color, std::string name)
        : AbstStaticObject(x, y, w, h, color, name) {}

private:
};
