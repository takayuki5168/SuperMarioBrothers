#pragma once

#include "include/abst_fix_object.hpp"

class BrickBlock : public AbstFixObject
{
public:
    BrickBlock(int x, int y)
        : AbstFixObject(x, y, 0x8d3800, "BrickBlock") {}
private:
};
