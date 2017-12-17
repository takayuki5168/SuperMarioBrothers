#pragma once

#include <vector>
#include "include/abst_dynamic_object.hpp"

class AbstPlayer : public AbstDynamicObject
{
public:
    explicit AbstPlayer(int x, int y, int w, int h, int color, std::string name)
        : AbstDynamicObject(x, y, w, h, color, name) {}

private:
};
