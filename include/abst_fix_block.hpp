#pragma once

#include "include/abst_fix_object.hpp"

class AbstFixBlock : public AbstFixObject
{
public:
    AbstFixBlock(int x, int y, int color, std::string name)
        : AbstFixObject(x, y, color, name) {}

    static constexpr int getBlockSize() { return m_block_size; }

private:
    static const int m_block_size = AbstFixObject::getObjectSize();
};
