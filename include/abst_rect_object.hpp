#pragma once

#include <vector>
#include "include/abst_object.hpp"

class AbstRectObject : public AbstObject
{
public:
    AbstRectObject(int x, int y, int w, int h, int color, std::string name)
        : AbstObject(x, y, w, h, color, name) {}

private:
};
