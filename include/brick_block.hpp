#pragma once

#include "include/abst_fix_block.hpp"

class BrickBlock : public AbstFixBlock
{
public:
    BrickBlock(int x, int y)
        : AbstFixBlock(x, y, 0x8d3800, "BrickBlock") {}
private:
};
