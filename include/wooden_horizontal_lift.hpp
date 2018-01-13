#pragma once

#include "include/abst_unique_object.hpp"

class WoodenHorizontalLift : public AbstUniqueObject
{
public:
    WoodenHorizontalLift(int x, int y)
        : AbstUniqueObject(x, y, m_width, m_height, 0x8d3800, "WoodenHorizontalLift") {}

    virtual void updatePosDecorator(double time)
    {
        int t = static_cast<int>(time);
        int po = (t - t % TIME_STEP) / TIME_STEP;
        if (po % 2 == 0) {  //4 == 1 or po % 4 == 2) {
            setVelY(-1);
            //updateVelY(-0.01);
        } else {
            setVelY(1);
            //updateVelY(0.01);
        }
    }

private:
    static constexpr int m_width = 120;
    static constexpr int m_height = 40;

    static constexpr int TIME_STEP = 2000;
};
