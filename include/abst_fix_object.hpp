#pragma once

#include "include/abst_object.hpp"

class AbstFixObject : public AbstObject
{
public:
    AbstFixObject(int x, int y, int color, std::string name)
        : AbstObject(x, y, m_object_size, m_object_size, color, name) {}

    static constexpr int getObjectSize() { return m_object_size; }

private:
    static const int m_object_size = 40;
};
