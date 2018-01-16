#pragma once

#include "include/abst_rect_object.hpp"

class WoodenVirticalLift : public AbstRectObject
{
public:
    WoodenVirticalLift(int x, int y)
        : AbstRectObject(x, y, LIFT_WIDTH, LIFT_HEIGHT, 0x8d3800, "WoodenVirticalLift") {}

    virtual void updatePosDecorator(double time)
    {
        int t = static_cast<int>(time);
        int po = (t - t % TIME_STEP) / TIME_STEP;
        if (po % 2 == 0) {
            setVelY(-1);
        } else {
            setVelY(1);
        }
    }

private:
    int LIFT_WIDTH = Params::BLOCK_SIZE * 3;
    int LIFT_HEIGHT = Params::BLOCK_SIZE * 1;

    static constexpr int TIME_STEP = 2000;
};
