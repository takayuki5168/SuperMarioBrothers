#pragma once

#include "include/abst_object.hpp"

class AbstFixBlock : public AbstObject
{
public:
    AbstFixBlock(int x, int y, int color, std::string name)
        : AbstObject(x, y, m_block_size, m_block_size, color, name) {}

    void updatePos() override {}

    static int getBlockSize() { return m_block_size; }

private:
    static const int m_block_size = 40;
};
