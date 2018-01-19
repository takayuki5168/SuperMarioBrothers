#pragma once

#include "include/abst_rect_object.hpp"

class WoodenCircleLift : public AbstRectObject
{
public:
    WoodenCircleLift(int x, int y, double time)
        : AbstRectObject(x, y, LIFT_WIDTH, LIFT_HEIGHT, 0x8d3800, "WoodenCircleLift"), m_center_pos(Point{x, y}), m_start_time(time) {}

    virtual void updatePosDecorator(double time)
    {
        int t = static_cast<int>(time) - m_start_time;
        int po = (t - t % TIME_STEP) / TIME_STEP;
        double x = m_center_pos.m_x + 90 * std::sin(time / 4000 * 2 * Params::PI);
        double y = m_center_pos.m_y + 90 * std::cos(time / 4000 * 2 * Params::PI);
        setPos(Point{x, y});
    }

private:
    // TODO static constexpr にしないとwidthとheightがどんどん大きくなる
    static constexpr int LIFT_WIDTH = Params::BLOCK_SIZE * 3;
    static constexpr int LIFT_HEIGHT = Params::BLOCK_SIZE * 1;

    double m_start_time = 0;

    static constexpr int TIME_STEP = 2000;
    Point m_center_pos;
};
