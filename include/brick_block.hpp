#pragma once

#include "include/abst_rect_object.hpp"

class BrickBlock : public AbstRectObject
{
public:
    BrickBlock(int x, int y)
        : AbstRectObject(x, y, BLOCK_SIZE, BLOCK_SIZE, 0x8d3800, "BrickBlock") {}
private:
    int BLOCK_SIZE = Params::BLOCK_SIZE;
};
