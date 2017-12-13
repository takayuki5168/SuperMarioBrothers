#pragma once

#include "include/abst_object.hpp"

class AbstCharactor : public AbstObject
{
public:
    AbstCharactor(int x, int y, int w, int h, int color, std::string name,
        std::vector<Point> collision_point, std::vector<Line> collision_frame)
        : AbstObject(x, y, w, h, color, name, collision_point, collision_frame) {}

    void updatePos() override
    {
        m_vel.y = 1;
        m_pos.y += m_vel.y;
    }

private:
    double hit_point = 0;
};
