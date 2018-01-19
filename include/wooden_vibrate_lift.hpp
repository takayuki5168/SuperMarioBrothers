#pragma once

#include "include/abst_rect_object.hpp"

class WoodenVibrateLift : public AbstRectObject
{
public:
    WoodenVibrateLift(int x, int y, double time)
        : AbstRectObject(x, y, LIFT_WIDTH, LIFT_HEIGHT, 0x8d3800, "WoodenVirticalLift"), m_start_time(time) {}

    virtual void updatePosDecorator(double time)
    {
        int t = static_cast<int>(time) - m_start_time;
        int po = (t - t % TIME_STEP) / TIME_STEP;
        if (po % 2 == 0) {
            setVelY(-1);
        } else {
            setVelY(1);
        }
    }

private:
    double m_start_time = 0;
    static constexpr int LIFT_WIDTH = Params::BLOCK_SIZE * 3;
    static constexpr int LIFT_HEIGHT = Params::BLOCK_SIZE * 1;

    static constexpr int TIME_STEP = 2000;
};
