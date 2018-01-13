#pragma once

#include "include/abst_unique_object.hpp"

class WoodenCircleLift : public AbstUniqueObject
{
public:
    WoodenCircleLift(int x, int y)
        : AbstUniqueObject(x, y, m_width, m_height, 0x8d3800, "WoodenCircleLift"), m_center_pos(Point{x, y}) {}

    virtual void updatePosDecorator(double time)
    {
        int t = static_cast<int>(time);
        int po = (t - t % TIME_STEP) / TIME_STEP;
        double x = m_center_pos.x + 90 * std::sin(time / 4000 * 2 * Params::PI);
        double y = m_center_pos.y + 90 * std::cos(time / 4000 * 2 * Params::PI);
        setPos(Point{x, y});
    }

private:
    static constexpr int m_width = 120;
    static constexpr int m_height = 40;

    static constexpr int TIME_STEP = 2000;
    Point m_center_pos;
};
