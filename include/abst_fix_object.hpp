#pragma once

#include "include/abst_static_object.hpp"

class AbstFixObject : public AbstStaticObject
{
public:
    explicit AbstFixObject(int x, int y, int color, std::string name)
        : AbstStaticObject(x, y, m_object_size, m_object_size, color, name) {}

    static constexpr int getObjectSize() { return m_object_size; }

private:
    static constexpr int m_object_size = 40;
};
